lg_tokenMatch(SDB *sdb, const SECItem *dbKey, CK_OBJECT_HANDLE class,
		const CK_ATTRIBUTE *templ, CK_ULONG count)
{
    PRBool match = PR_TRUE;
    LGObjectCache *obj = lg_NewObjectCache(sdb, dbKey, class);
    unsigned int i;

    if (obj == NULL) {
	return PR_FALSE;
    }

    for (i=0; i < count; i++) {
	match = lg_cmpAttribute(obj, &templ[i]);
	if (!match) {
	   break;
	}
    }


    lg_DestroyObjectCache(obj);


    return match;
}
