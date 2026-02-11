eir_parse_uuid128(struct eir_data *eir, uint8_t *data, uint8_t len)
{
	uint8_t *uuid_ptr = data;
	uuid_t service;
	char *uuid_str;
	unsigned int i;
	int k;

	service.type = SDP_UUID128;
	for (i = 0; i < len / 16; i++) {
		for (k = 0; k < 16; k++)
			service.value.uuid128.data[k] = uuid_ptr[16 - k - 1];
		uuid_str = bt_uuid2string(&service);
		eir->services = g_slist_append(eir->services, uuid_str);
		uuid_ptr += 16;
	}
}
