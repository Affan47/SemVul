agattrsym(void *obj, char *name)
{
    Agattr_t *data;
    Agsym_t *rv;
    char *arg = name;

    data = agattrrec((Agobj_t *) obj);
    if (data)
	rv = agdictsym(data->dict, arg);
    else
	rv = NILsym;
    return rv;
}
