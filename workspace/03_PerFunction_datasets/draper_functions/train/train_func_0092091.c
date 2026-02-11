custom_attrs_defined_internal (MonoObject *obj, MonoReflectionType *attr_type)
{
	MonoClass *attr_class = mono_class_from_mono_type (attr_type->type);
	MonoCustomAttrInfo *cinfo;
	gboolean found;

	mono_class_init_or_throw (attr_class);

	cinfo = mono_reflection_get_custom_attrs_info (obj);
	if (!cinfo)
		return FALSE;
	found = mono_custom_attrs_has_attr (cinfo, attr_class);
	if (!cinfo->cached)
		mono_custom_attrs_free (cinfo);
	return found;
}
