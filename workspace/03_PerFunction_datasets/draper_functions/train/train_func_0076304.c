acl_set_ext (ext_type type, void *object, void *data)
{
	if ( type < ACL_EXT_ALL )
	{
		struct acl_ext ext = acl_ext_list [type];
		slapi_set_object_extension ( ext.object_type, object, ext.handle, data );
	}
}
