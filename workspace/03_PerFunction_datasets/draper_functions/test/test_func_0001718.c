dbpriv_check_properties_for_chparent(Objid oid, Objid new_parent)
{
    Object *o;
    int i;

    for (o = dbpriv_find_object(new_parent);
	 o;
	 o = dbpriv_find_object(o->parent)) {
	Proplist *props = &o->propdefs;

	for (i = 0; i < props->cur_length; i++)
	    if (property_defined_at_or_below(props->l[i].name,
					     props->l[i].hash,
					     oid))
		return 0;
    }

    return 1;
}
