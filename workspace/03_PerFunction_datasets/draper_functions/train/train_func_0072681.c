dattrib(Object o, struct fmt_info *p)
{
    Object subo;
    char *name;
    int i, rc;

    for(i=0; (subo=DXGetEnumeratedAttribute(o, i, &name)); i++)
	if (!has_shorthand(subo, NULL)) {
	    rc = _dxfObject_Format(subo, p);
	    if (rc != OK)
		return ERROR;
	}

    return OK;
}
