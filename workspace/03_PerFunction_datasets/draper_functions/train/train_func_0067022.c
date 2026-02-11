secmod_AddModuleToList(SECMODModuleList **moduleList,SECMODModule *newModule)
{
    SECMODModuleList *mlp, *newListElement, *last = NULL;

    newListElement = SECMOD_NewModuleListElement();
    if (newListElement == NULL) {
	return SECFailure;
    }

    newListElement->module = SECMOD_ReferenceModule(newModule);

    SECMOD_GetWriteLock(moduleLock);


    for(mlp = *moduleList; mlp != NULL; mlp = mlp->next) {
	last = mlp;
    }

    if (last == NULL) {
	*moduleList = newListElement;
    } else {
	SECMOD_AddList(last,newListElement,NULL);
    }
    SECMOD_ReleaseWriteLock(moduleLock);
    return SECSuccess;
}
