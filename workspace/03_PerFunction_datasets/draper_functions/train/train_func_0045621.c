virt_efi_reset_system(int reset_type,
				  efi_status_t status,
				  unsigned long data_size,
				  efi_char16_t *data)
{
	unsigned long flags;

	spin_lock_irqsave(&efi_runtime_lock, flags);
	__efi_call_virt(reset_system, reset_type, status, data_size, data);
	spin_unlock_irqrestore(&efi_runtime_lock, flags);
}
