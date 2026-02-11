virt_efi_get_variable(efi_char16_t *name,
					  efi_guid_t *vendor,
					  u32 *attr,
					  unsigned long *data_size,
					  void *data)
{
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&efi_runtime_lock, flags);
	status = efi_call_virt(get_variable, name, vendor, attr, data_size,
			       data);
	spin_unlock_irqrestore(&efi_runtime_lock, flags);
	return status;
}
