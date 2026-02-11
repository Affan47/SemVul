ms_obj_attr_bag_lookup (MSObjAttrBag *attrs, MSObjAttrID id)
{
	if (attrs != NULL) {
		MSObjAttr attr = {0, {0}};
		*((MSObjAttrID *)&(attr.id)) = id;
		return g_hash_table_lookup (attrs, &attr);
	}
	return NULL;
}
