cbdataAddType(cbdata_type type, const char *name, int size, FREE * free_func)
{
    if (type)
	return type;
    type = cbdata_types;
    cbdataInitType(type, name, size, free_func);
    return type;
}
