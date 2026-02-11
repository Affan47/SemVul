db_set_property_flags(db_prop_handle h, unsigned flags)
{
    if (h.built_in)
	panic("Built-in property in DB_SET_PROPERTY_FLAGS!");
    else {
	Pval *prop = h.ptr;

	prop->perms = flags;
    }
}
