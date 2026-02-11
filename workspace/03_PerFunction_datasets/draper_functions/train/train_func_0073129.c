atk_pack_print(char *buf, size_t sz, union acpi_object *pack)
{
	int ret;
	int i;

	for (i = 0; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.elements[i];

		ret = atk_acpi_print(buf, sz, obj);
		if (ret >= sz)
			break;
		buf += ret;
		sz -= ret;
	}
}
