dump_rsdp(s_acpi * acpi, ZZJSON_CONFIG * config, ZZJSON ** item)
{
	char valid[8]={0};
	snprintf(valid,sizeof(valid),"%s","false");
	if (acpi->rsdp.valid) {
		snprintf(valid,sizeof(valid),"%s","true");
	}
	CREATE_ARRAY
		add_as("acpi.item","rsdp")
		add_as("acpi.rsdp.is_valid",valid)
	END_OF_ARRAY;

	if (acpi->rsdp.valid==false) {
		FLUSH_OBJECT;
		return;
	}

	s_rsdp *r = &acpi->rsdp;
	char revision[10]={0};
	char address[16]={0};
	char oem_id[16]={0};
	snprintf(revision,sizeof(revision),"0x%03x",r->revision);
	snprintf(address,sizeof(address),"%p",r->address);
	snprintf(oem_id,sizeof(oem_id),"%s",r->oem_id);
	APPEND_ARRAY
		add_as("acpi.rsdp.revision",revision)
		add_as("acpi.rsdp.oem_id",oem_id)
		add_as("acpi.rsdp.address",address)
	END_OF_APPEND;

	FLUSH_OBJECT;

}
