db_object_sort_func (GdaMetaDbObject *dbo1, GdaMetaDbObject *dbo2)
{
	gint retval = 0;
	if (dbo1->obj_schema && dbo2->obj_schema) {
		retval = strcmp (dbo1->obj_schema, dbo2->obj_schema);
		if (retval)
			return retval;
	}
	else if (dbo1->obj_schema)
		return 1;
	else if (dbo2->obj_schema)
		return -1;

	if (dbo1->obj_name && dbo2->obj_name)
		return strcmp (dbo1->obj_name, dbo2->obj_name);
	else if (dbo1->obj_name)
		return 1;
	else if (dbo2->obj_name)
		return -1;
	return 0;
}
