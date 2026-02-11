xc_core_create_pfn_tables(void)
{
        if (xd->flags & XC_CORE_P2M_CREATE) {
		if (!machdep->xendump_p2m_create)
			error(FATAL,
			    "xen xc_core dumpfiles not supported on this architecture");

		if (!machdep->xendump_p2m_create((void *)xd))
			error(FATAL,
			    "cannot create xen pfn-to-mfn mapping\n");
	}

	if (xd->flags & XC_CORE_ELF)
		xc_core_elf_pfn_init();

	xd->flags &= ~(XC_CORE_P2M_CREATE|XC_CORE_PFN_CREATE);

	if (CRASHDEBUG(1))
		xendump_memory_dump(xd->ofp);
}
