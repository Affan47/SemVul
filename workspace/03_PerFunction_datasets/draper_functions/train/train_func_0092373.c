SECMOD_FindModuleByID(SECMODModuleID id)
{
    SECMODModuleList *mlp;
    SECMODModule *module = NULL;

    if (!moduleLock) {
    	PORT_SetError(SEC_ERROR_NOT_INITIALIZED);
	return module;
    }
    SECMOD_GetReadLock(moduleLock);
    for(mlp = modules; mlp != NULL; mlp = mlp->next) {
	if (id == mlp->module->moduleID) {
	    module = mlp->module;
	    SECMOD_ReferenceModule(module);
	    break;
	}
    }
    SECMOD_ReleaseReadLock(moduleLock);
    if (module == NULL) {
	PORT_SetError(SEC_ERROR_NO_MODULE);
    }
    return module;
}
