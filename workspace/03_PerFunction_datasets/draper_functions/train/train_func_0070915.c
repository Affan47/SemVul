x86_64_display_memmap(void)
{
        ulong e820;
        int nr_map, i;
        char *buf, *e820entry_ptr;
        ulonglong addr, size;
        uint type;

        e820 = symbol_value("e820");
	if (CRASHDEBUG(1))
		dump_struct("e820map", e820, RADIX(16));
        buf = (char *)GETBUF(SIZE(e820map));

        readmem(e820, KVADDR, &buf[0], SIZE(e820map),
                "e820map", FAULT_ON_ERROR);

        nr_map = INT(buf + OFFSET(e820map_nr_map));

        fprintf(fp, "      PHYSICAL ADDRESS RANGE         TYPE\n");

        for (i = 0; i < nr_map; i++) {
                e820entry_ptr = buf + sizeof(int) + (SIZE(e820entry) * i);
                addr = ULONGLONG(e820entry_ptr + OFFSET(e820entry_addr));
                size = ULONGLONG(e820entry_ptr + OFFSET(e820entry_size));
                type = UINT(e820entry_ptr + OFFSET(e820entry_type));
		fprintf(fp, "%016llx - %016llx  ", addr, addr+size);
		if (type >= (sizeof(e820type)/sizeof(char *)))
			fprintf(fp, "type %d\n", type);
		else
			fprintf(fp, "%s\n", e820type[type]);
        }
}
