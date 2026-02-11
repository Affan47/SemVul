resolv(const char *name)
{
    com32sys_t reg;

    strcpy((char *)__com32.cs_bounce, name);

    memset(&reg, 0, sizeof reg);
    reg.eax.w[0] = 0x0010;
    reg.ebx.w[0] = OFFS(__com32.cs_bounce);
    reg.es = SEG(__com32.cs_bounce);

    __intcall(0x22, &reg, &reg);

    if (reg.eflags.l & EFLAGS_CF)
	return 0;
    else
	return reg.eax.l;
}
