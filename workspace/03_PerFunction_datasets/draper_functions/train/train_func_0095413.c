_dxfMakeUnOp(int op, PTreeNode *arg)
{
    PTreeNode  *res;

    if (arg == NULL) {
	DXSetError (ERROR_INTERNAL, "_dxfMakeUnOp, insufficient arguments");
	return(NULL);
    }


    res = _dxfMakeArg (op);
    if (res == NULL) {
	_dxfComputeFreeTree (arg);
	return(NULL);
    }
    OPRL_INIT (res, arg);
    arg->next = NULL;

    return(res);
}
