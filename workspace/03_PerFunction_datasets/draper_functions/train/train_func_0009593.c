uuid2str(struct tupla *message, const uuid_t *uuid, char *str, size_t n)
{
	char *str2;

	if (!uuid) {
		snprintf(str, n, "NULL");
		return -2;
	}

	switch (uuid->type) {
	case SDP_UUID16:
		str2 = string_lookup(message, uuid->value.uuid16);
		snprintf(str, n, "%s", str2);
		break;
	case SDP_UUID32:
		str2 = string_lookup(message, uuid->value.uuid32);
		snprintf(str, n, "%s", str2);
		break;
	case SDP_UUID128:
		str2 = string_lookup_uuid(message, uuid);
		snprintf(str, n, "%s", str2);
		break;
	default:
		snprintf(str, n, "Type of UUID (%x) unknown.", uuid->type);
		return -1;
	}

	return 0;
}
