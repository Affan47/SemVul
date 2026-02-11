do_vmbus_entry(const char *filename, void *symval,
			  char *alias)
{
	int i;
	DEF_FIELD_ADDR(symval, hv_vmbus_device_id, guid);
	char guid_name[(sizeof(*guid) + 1) * 2];

	for (i = 0; i < (sizeof(*guid) * 2); i += 2)
		sprintf(&guid_name[i], "%02x", TO_NATIVE((guid->b)[i/2]));

	strcpy(alias, "vmbus:");
	strcat(alias, guid_name);

	return 1;
}
