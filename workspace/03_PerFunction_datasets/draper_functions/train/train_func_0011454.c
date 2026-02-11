dump_table(struct upload_backend *be,
		       const char name[], const void *ptr, uint32_t len)
{
    char namebuf[64];
    uint32_t name_key = *(uint32_t *)name;

    if (rb_has(&rb_addrs, (size_t)ptr))
	return;

    if (!rb_has(&rb_types, name_key)) {
	snprintf(namebuf, sizeof namebuf, "acpi/%4.4s", name);
	cpio_mkdir(be, namebuf);
    }

    snprintf(namebuf, sizeof namebuf, "acpi/%4.4s/%08x", name, (uint32_t)ptr);
    cpio_hdr(be, MODE_FILE, len, namebuf);

    write_data(be, ptr, len);
}
