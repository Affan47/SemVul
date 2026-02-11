detect_memory_e820(struct e820entry *desc, int size_map, int *size_found)
{
    int count = 0;
    static struct e820_ext_entry buf;

    com32sys_t ireg, oreg;
    memset(&ireg, 0, sizeof ireg);

    ireg.eax.w[0] = 0xe820;
    ireg.edx.l = SMAP;
    ireg.ecx.l = sizeof(struct e820_ext_entry);
    ireg.edi.w[0] = OFFS(__com32.cs_bounce);
    ireg.es = SEG(__com32.cs_bounce);


    memset(&buf, 0, sizeof buf);
    buf.ext_flags = 1;

    do {
	memcpy(__com32.cs_bounce, &buf, sizeof buf);


	__intcall(0x15, &ireg, &oreg);


	if (oreg.eax.l != SMAP) {
	    count = 0;
	    break;
	}

	if (oreg.eflags.l & EFLAGS_CF || oreg.ecx.l < 20)
	    break;

	memcpy(&buf, __com32.cs_bounce, sizeof buf);


	if (oreg.ecx.l > 20 && !(buf.ext_flags & 1))
	    continue;

	memcpy(&desc[count], &buf, sizeof buf);
	count++;


	ireg.ebx.l = oreg.ebx.l;
    } while (ireg.ebx.l && count < size_map);

    *size_found = count;
}
