fops_get_device_handle(CHAR16 *name, EFI_HANDLE *dev)
{
	UINTN i;

	if (name == NULL || dev == NULL) return EFI_INVALID_PARAMETER;

	for(i=0; i < ndev; i++) {
		if (!StrCmp(dev_tab[i].name, name)) goto found;
	}
	return EFI_NOT_FOUND;
found:
	*dev = dev_tab[i].dev;

	return EFI_SUCCESS;
}
