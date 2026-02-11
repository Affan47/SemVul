bluetooth_simple_device_copy (gpointer boxed)
{
	BluetoothSimpleDevice* origin = (BluetoothSimpleDevice*) boxed;

	BluetoothSimpleDevice* result = g_new (BluetoothSimpleDevice, 1);
	result->bdaddr = g_strdup (origin->bdaddr);
	result->device_path = g_strdup (origin->device_path);
	result->alias = g_strdup (origin->alias);
	result->connected = origin->connected;
	result->can_connect = origin->can_connect;
	result->capabilities = origin->capabilities;
	result->type = origin->type;

	return (gpointer)result;
}
