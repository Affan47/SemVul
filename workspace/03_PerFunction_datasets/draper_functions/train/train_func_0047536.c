i2c_sysfs_delete_device(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct i2c_adapter *adap = to_i2c_adapter(dev);
	struct i2c_client *client, *next;
	unsigned short addr;
	char end;
	int res;


	res = sscanf(buf, "%hi%c", &addr, &end);
	if (res < 1) {
		dev_err(dev, "%s: Can't parse I2C address\n", "delete_device");
		return -EINVAL;
	}
	if (res > 1  && end != '\n') {
		dev_err(dev, "%s: Extra parameters\n", "delete_device");
		return -EINVAL;
	}


	res = -ENOENT;
	mutex_lock_nested(&adap->userspace_clients_lock,
			  i2c_adapter_depth(adap));
	list_for_each_entry_safe(client, next, &adap->userspace_clients,
				 detected) {
		if (i2c_encode_flags_to_addr(client) == addr) {
			dev_info(dev, "%s: Deleting device %s at 0x%02hx\n",
				 "delete_device", client->name, client->addr);

			list_del(&client->detected);
			i2c_unregister_device(client);
			res = count;
			break;
		}
	}
	mutex_unlock(&adap->userspace_clients_lock);

	if (res < 0)
		dev_err(dev, "%s: Can't find device in list\n",
			"delete_device");
	return res;
}
