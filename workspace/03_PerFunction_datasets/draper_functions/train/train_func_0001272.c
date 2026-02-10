_dxfComputeCheckSameTypeSpecReturn (PTreeNode *pt, ObjStruct *os, OperBinding *binding)
{
    PTreeNode *subTree;
    int listElement;
    int items = pt->metaType.items;
    int count;


    if (binding->numArgs != -1) {
	for (count = 0, subTree = pt->args;
	     subTree != NULL;
	     ++count, subTree = subTree->next)
	;
	if (count != binding->numArgs) {
	    DXSetError(ERROR_BAD_TYPE, "#11945", binding->numArgs);
	    return (ERROR);
	}
    }
    else if (pt->args == NULL) {
	return (ERROR);
    }


    pt->metaType = pt->args->metaType;
    pt->metaType.items = items;

    listElement = 0;
    subTree = pt->args;

    while (subTree != NULL) {
	if (subTree->metaType.type != binding->inTypes[0].type ||
	    _dxfComputeCompareType (&pt->metaType, &subTree->metaType) == ERROR) {
	    return (ERROR);
	}
	subTree = subTree->next;
	++listElement;
    }

    pt->metaType = binding->outType;
    pt->metaType.items = items;
    pt->impl = binding->impl;
    return (OK);
}
