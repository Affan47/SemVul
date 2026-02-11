cui_dbus_get_fixed_array(DBusMessageIter *iter,
					int *length,
					void *destination)
{
	DBusMessageIter farray;

	if (length == NULL || destination == NULL)
		return -EINVAL;

	if (dbus_message_iter_get_arg_type(iter) != DBUS_TYPE_ARRAY)
		return -EINVAL;

	if (dbus_message_iter_get_element_type(iter) != DBUS_TYPE_BYTE)
		return -EINVAL;

	dbus_message_iter_recurse(iter, &farray);

	dbus_message_iter_get_fixed_array(&farray, destination, length);

	return 0;
}
