jaw_impl_get_interface_data (JawObject *jaw_obj, guint iface)
{
	JawImpl *jaw_impl = (JawImpl*)jaw_obj;

	if (jaw_impl == NULL || jaw_impl->ifaceTable == NULL) {
		return NULL;
	}

	JawInterfaceInfo *info = g_hash_table_lookup(jaw_impl->ifaceTable, (gpointer)iface);

	if (info) {
		return info->data;
	}

	return NULL;
}
