rmi_check_sanity(struct hid_device *hdev, u8 *data, int size)
{
	int valid_size = size;


	while ((data[valid_size - 1] == 0xff) && valid_size > 0)
		valid_size--;

	return valid_size;
}
