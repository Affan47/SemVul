post_unmap_gar_callback(struct apei_exec_context *ctx,
				   struct acpi_whea_header *entry,
				   void *data)
{
	u8 ins = entry->instruction;

	if (ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER)
		apei_unmap_generic_address(&entry->register_region);

	return 0;
}
