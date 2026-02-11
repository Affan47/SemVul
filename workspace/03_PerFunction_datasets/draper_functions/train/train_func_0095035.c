secmod_GetConfigList(PRBool isFIPS, char *spec, int *count)
{
    char **children;
    CK_SLOT_ID *ids;
    char *strippedSpec;
    int childCount;
    SECMODConfigList *conflist = NULL;
    int i;

    strippedSpec = secmod_ParseModuleSpecForTokens(PR_TRUE, isFIPS,
						spec,&children,&ids);
    if (strippedSpec == NULL) {
	return NULL;
    }

    for (childCount=0; children && children[childCount]; childCount++) ;
    *count = childCount+1;
    conflist = PORT_NewArray(SECMODConfigList,*count);
    if (conflist == NULL) {
	*count = 0;
	goto loser;
    }

    conflist[0].config = secmod_getConfigDir(strippedSpec,
					    &conflist[0].certPrefix,
					    &conflist[0].keyPrefix,
					    &conflist[0].isReadOnly);
    for (i=0; i < childCount; i++) {
	conflist[i+1].config = secmod_getConfigDir(children[i],
					    &conflist[i+1].certPrefix,
					    &conflist[i+1].keyPrefix,
					    &conflist[i+1].isReadOnly);
    }

loser:
    secmod_FreeChildren(children, ids);
    PORT_Free(strippedSpec);
    return conflist;
}
