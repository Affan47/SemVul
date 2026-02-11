ExVCRGet (char *var)
{
    gvar	*gv;
    Array	arr;
    int		val = 0;

    if ((gv = (gvar *) _dxf_ExVariableSearch (var, vcr_dict)) == NULL)
	return (0);

    arr = (Array)  gv->obj;

    DXExtractInteger ((Object) arr, &val);

    ExDelete (gv);

    return (val);
}
