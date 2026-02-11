f_old(const char *f_name)
{
	if (ds_state != dsInactive)
		for (uint i = 0; i < fields_object->size(); i++)
			if ((*fields_object)[i].props.name == f_name)
				return (*fields_object)[i].val;
	field_value fv;

	return fv;
}
