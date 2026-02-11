DXGetVariable(char *name, Object *obj)
{
    vargetArg *va;
    int ret;

    va = (vargetArg *) DXAllocate(sizeof(vargetArg));
    va->name = name;
    ret = _dxf_ExRunOn (1, ExVariableGet, va, 0);

    if (ret == OK)
	*obj = va->obj;
    else
	*obj = NULL;

    DXFree(va);
    return (ret);
}
