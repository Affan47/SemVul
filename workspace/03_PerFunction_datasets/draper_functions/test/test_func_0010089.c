_dxfMakeVariable(char *name)
{
    PTreeNode *res;

    res = _dxfMakeArg (OPER_VARIABLE);
    if (res == NULL) {
	return(NULL);
    }

    strncpy (res->u.s, name, MAX_CA_STRING);

    return(res);
}
