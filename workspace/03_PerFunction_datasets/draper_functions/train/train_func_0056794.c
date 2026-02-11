DXSetVariable(char *name, Object obj, int sync, int cause_execution)
{
    varupdateArg *va;
    int ret;

    ExDebug("*1","Setting Var %s to obj %x", name, obj);
    if (DXProcessorId() == 0) {
        _dxf_ExUpdateGlobalDict(name, obj, cause_execution);
        return(OK);
    }

    va = (varupdateArg *) DXAllocate(sizeof(varupdateArg));
    va->name = name;
    va->obj = obj;
    va->cause_execution = cause_execution;
    if(sync) {
        ret = _dxf_ExRunOn (1, ExVariableSet, va, 0);
        return(ret);
    }
    else {
        _dxf_ExRQEnqueue(ExVariableSet, (Pointer)va, 1, 0, 1, 0);
        return(OK);
    }

}
