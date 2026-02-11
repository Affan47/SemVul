syslinux_font_query(uint8_t **font)
{
    static com32sys_t ireg;
    com32sys_t oreg;
    int height;

    ireg.eax.w[0] = 0x0018;
    __intcall(0x22, &ireg, &oreg);

    height = !(oreg.eflags.l & EFLAGS_CF) ? oreg.eax.b[0] : 0;
    if (height)
	*font = MK_PTR(oreg.es, oreg.ebx.w[0]);

    return height;
}
