virt_efi_query_variable_info(u32 attr,
						 u64 *storage_space,
						 u64 *remaining_space,
						 u64 *max_variable_size)
{
	unsigned long flags;
	efi_status_t status;

	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	spin_lock_irqsave(&efi_runtime_lock, flags);
	status = efi_call_virt(query_variable_info, attr, storage_space,
			       remaining_space, max_variable_size);
	spin_unlock_irqrestore(&efi_runtime_lock, flags);
	return status;
}
