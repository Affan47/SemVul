nssTokenObjectCache_GetObjectAttributes (
  nssTokenObjectCache *cache,
  NSSArena *arenaOpt,
  nssCryptokiObject *object,
  CK_OBJECT_CLASS objclass,
  CK_ATTRIBUTE_PTR atemplate,
  CK_ULONG atlen
)
{
    PRUint32 i, j;
    NSSArena *arena = NULL;
    nssArenaMark *mark = NULL;
    nssCryptokiObjectAndAttributes *cachedOA = NULL;
    nssCryptokiObjectAndAttributes **oa = NULL;
    PRUint32 objectType;
    if (!token_is_present(cache)) {
	return PR_FAILURE;
    }
    PZ_Lock(cache->lock);
    switch (objclass) {
    case CKO_CERTIFICATE:    objectType = cachedCerts; break;
    case CKO_NETSCAPE_TRUST: objectType = cachedTrust; break;
    case CKO_NETSCAPE_CRL:   objectType = cachedCRLs;  break;
    default: goto loser;
    }
    if (!cache_available_for_object_type(cache, objectType)) {
	goto loser;
    }
    oa = cache->objects[objectType];
    if (!oa) {
	goto loser;
    }
    for (; *oa; oa++) {
	if (nssCryptokiObject_Equal((*oa)->object, object)) {
	    cachedOA = *oa;
	    break;
	}
    }
    if (!cachedOA) {
	goto loser;
    }
    if (arenaOpt) {
	arena = arenaOpt;
	mark = nssArena_Mark(arena);
    }
    for (i=0; i<atlen; i++) {
	for (j=0; j<cachedOA->numAttributes; j++) {
	    if (atemplate[i].type == cachedOA->attributes[j].type) {
		CK_ATTRIBUTE_PTR attr = &cachedOA->attributes[j];
		if (cachedOA->attributes[j].ulValueLen == 0 ||
		    cachedOA->attributes[j].ulValueLen == (CK_ULONG)-1)
		{
		    break;
		}
		if (atemplate[i].ulValueLen > 0) {
		    if (atemplate[i].pValue == NULL ||
		        atemplate[i].ulValueLen < attr->ulValueLen)
		    {
			goto loser;
		    }
		} else {
		    atemplate[i].pValue = nss_ZAlloc(arena, attr->ulValueLen);
		    if (!atemplate[i].pValue) {
			goto loser;
		    }
		}
		nsslibc_memcpy(atemplate[i].pValue,
		               attr->pValue, attr->ulValueLen);
		atemplate[i].ulValueLen = attr->ulValueLen;
		break;
	    }
	}
	if (j == cachedOA->numAttributes) {
	    atemplate[i].ulValueLen = (CK_ULONG)-1;
	}
    }
    PZ_Unlock(cache->lock);
    if (mark) {
	nssArena_Unmark(arena, mark);
    }
    return PR_SUCCESS;
loser:
    PZ_Unlock(cache->lock);
    if (mark) {
	nssArena_Release(arena, mark);
    }
    return PR_FAILURE;
}
