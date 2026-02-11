smime_init_caps (void)
{
    smime_capability *cap;
    smime_cipher_map *map;
    SECOidData *oiddata;
    SECStatus rv;
    int i;

    if (smime_encoded_caps != NULL && (! smime_prefs_changed))
	return SECSuccess;

    if (smime_encoded_caps != NULL) {
	SECITEM_FreeItem (smime_encoded_caps, PR_TRUE);
	smime_encoded_caps = NULL;
    }

    if (smime_capabilities == NULL) {
	smime_capabilities = (smime_capability**)PORT_ZAlloc (
					  (smime_symmetric_count + 1)
					  * sizeof(smime_capability *));
	if (smime_capabilities == NULL)
	    return SECFailure;
    }

    rv = SECFailure;


    for (i = 0; i < smime_current_pref_index; i++) {
	int mapi;


	mapi = smime_mapi_by_cipher (smime_prefs[i]);
	if (mapi < 0)
	    break;


	PORT_Assert (mapi < smime_symmetric_count);
	map = &(smime_cipher_maps[mapi]);


	cap = smime_capabilities[i];
	if (cap == NULL) {
	    cap = (smime_capability*)PORT_ZAlloc (sizeof(smime_capability));
	    if (cap == NULL)
		break;
	    smime_capabilities[i] = cap;
	} else if (cap->cipher == smime_prefs[i]) {
	    continue;
	}

	cap->capIDTag = map->algtag;
	oiddata = SECOID_FindOIDByTag (map->algtag);
	if (oiddata == NULL)
	    break;

	if (cap->capabilityID.data != NULL) {
	    SECITEM_FreeItem (&(cap->capabilityID), PR_FALSE);
	    cap->capabilityID.data = NULL;
	    cap->capabilityID.len = 0;
	}

	rv = SECITEM_CopyItem (NULL, &(cap->capabilityID), &(oiddata->oid));
	if (rv != SECSuccess)
	    break;

	if (map->parms == NULL) {
	    cap->parameters.data = NULL;
	    cap->parameters.len = 0;
	} else {
	    cap->parameters.data = map->parms->data;
	    cap->parameters.len = map->parms->len;
	}

	cap->cipher = smime_prefs[i];
    }

    if (i != smime_current_pref_index)
	return rv;

    while (i < smime_symmetric_count) {
	cap = smime_capabilities[i];
	if (cap != NULL) {
	    SECITEM_FreeItem (&(cap->capabilityID), PR_FALSE);
	    PORT_Free (cap);
	}
	smime_capabilities[i] = NULL;
	i++;
    }
    smime_capabilities[i] = NULL;

    smime_encoded_caps = SEC_ASN1EncodeItem (NULL, NULL, &smime_capabilities,
					     smime_capabilities_template);
    if (smime_encoded_caps == NULL)
	return SECFailure;

    return SECSuccess;
}
