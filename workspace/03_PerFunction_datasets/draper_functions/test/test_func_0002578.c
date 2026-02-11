property_defined_at(const char *pname, int phash, Objid oid)
{
    Proplist *props = &dbpriv_find_object(oid)->propdefs;
    int length = props->cur_length;
    int i;

    for (i = 0; i < length; i++)
	if (props->l[i].hash == phash
	    && !mystrcasecmp(props->l[i].name, pname))
	    return 1;

    return 0;
}
