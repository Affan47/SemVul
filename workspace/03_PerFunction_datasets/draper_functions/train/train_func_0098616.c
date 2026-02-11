syslinux_shuffle_boot_pm(struct syslinux_movelist *fraglist,
			     struct syslinux_memmap *memmap,
			     uint16_t bootflags, struct syslinux_pm_regs *regs)
{
    uint8_t handoff_code[9 * 5], *p;
    const uint32_t *rp;
    int i, rv;
    struct syslinux_memmap *tmap;
    addr_t regstub, stublen;

    tmap = syslinux_target_memmap(fraglist, memmap);
    if (!tmap)
	return -1;

    regstub = 0x800;
    stublen = sizeof handoff_code;
    rv = syslinux_memmap_find(tmap, SMT_FREE, &regstub, &stublen, 1);
    syslinux_free_memmap(tmap);
    if (rv)
	return -1;


    p = handoff_code;
    rp = (const uint32_t *)regs;
    for (i = 0; i < 8; i++) {
	*p = 0xb8 + i;
	*(uint32_t *) (p + 1) = *rp++;
	p += 5;
    }
    *p = 0xe9;
    *(uint32_t *) (p + 1) = regs->eip - regstub - sizeof handoff_code;


    if (syslinux_add_movelist(&fraglist, regstub, (addr_t) handoff_code,
			      sizeof handoff_code))
	return -1;

    return syslinux_do_shuffle(fraglist, memmap, regstub, 1, bootflags);
}
