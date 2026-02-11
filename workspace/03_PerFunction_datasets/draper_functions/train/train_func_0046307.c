_dxfPostFieldTask(Pointer ptr)
{
    int      dir;
    Array    comp;
    Field    field;
    TaskArgs *args;

    args = (TaskArgs *)ptr;

    dir   = args->dir;
    comp  = args->comp;
    field = args->field;

    if (! _dxfPostField(field, dir, comp))
	return ERROR;

    return OK;
}
