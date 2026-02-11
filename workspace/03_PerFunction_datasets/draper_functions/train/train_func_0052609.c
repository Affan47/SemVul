ListModules()
{
    SECMODListLock *lock;
    SECMODModuleList *list;
    SECMODModuleList *deadlist;
    SECMODModuleList *mlp;
    Error ret=UNSPECIFIED_ERR;
    int count = 0;

    lock = SECMOD_GetDefaultModuleListLock();
    if(!lock) {
	PR_fprintf(PR_STDERR, errStrings[NO_LIST_LOCK_ERR]);
	return NO_LIST_LOCK_ERR;
    }

    SECMOD_GetReadLock(lock);

    list = SECMOD_GetDefaultModuleList();
    deadlist = SECMOD_GetDeadModuleList();
    if (!list && !deadlist) {
	PR_fprintf(PR_STDERR, errStrings[NO_MODULE_LIST_ERR]);
	ret = NO_MODULE_LIST_ERR;
	goto loser;
    }

    PR_fprintf(PR_STDOUT,
	"\nListing of PKCS #11 Modules\n"
	"-----------------------------------------------------------\n");

    for(mlp=list; mlp != NULL; mlp = mlp->next) {
	printModule(mlp->module, &count);
    }
    for (mlp=deadlist; mlp != NULL; mlp = mlp->next) {
	printModule(mlp->module, &count);
    }


    PR_fprintf(PR_STDOUT,
	"-----------------------------------------------------------\n");

    ret = SUCCESS;

loser:
    SECMOD_ReleaseReadLock(lock);
    return ret;
}
