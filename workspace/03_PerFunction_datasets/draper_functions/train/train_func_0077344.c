_dxfComputeCheckStrings (PTreeNode *pt, ObjStruct *os, OperBinding *binding)
{
    int searchFailed;
    PTreeNode *arg;
    int j;
    int items = pt->metaType.items;

    searchFailed = 0;
    arg = pt->args;

    if (pt->args != NULL) {
	pt->metaType.shape[0] = pt->args->metaType.shape[0];
    }


    for (j = 0; !searchFailed && j < binding->numArgs && arg != NULL; ++j) {
	if (arg->metaType.rank != 1 ||
	    arg->metaType.type != binding->inTypes[j].type ||
	    arg->metaType.category != binding->inTypes[j].category) {

	    searchFailed = 1;
	}
	arg = arg->next;
    }
    if (!searchFailed) {
	if (arg != NULL || j != binding->numArgs) {
	    DXSetError(ERROR_BAD_TYPE, "#11945", binding->numArgs);
	    return (ERROR);
	}
	pt->impl = binding->impl;
	pt->metaType.type = binding->outType.type;
	pt->metaType.category = binding->outType.category;
	pt->metaType.rank = binding->outType.rank;
	pt->metaType.items = items;
	return (OK);
    }
    else {
	return (ERROR);
    }
}
