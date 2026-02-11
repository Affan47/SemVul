is_unsupported_vmbus_devs(const uuid_le *guid)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vmbus_unsupported_devs); i++)
		if (!uuid_le_cmp(*guid, vmbus_unsupported_devs[i].guid))
			return true;
	return false;
}
