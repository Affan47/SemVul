cfi_cmdset_unknown(struct map_info *map,
						  int primary)
{
	struct cfi_private *cfi = map->fldrv_priv;
	__u16 type = primary?cfi->cfiq->P_ID:cfi->cfiq->A_ID;
#ifdef CONFIG_MODULES
	char probename[sizeof(VMLINUX_SYMBOL_STR(cfi_cmdset_%4.4X))];
	cfi_cmdset_fn_t *probe_function;

	sprintf(probename, VMLINUX_SYMBOL_STR(cfi_cmdset_%4.4X), type);

	probe_function = __symbol_get(probename);
	if (!probe_function) {
		request_module("cfi_cmdset_%4.4X", type);
		probe_function = __symbol_get(probename);
	}

	if (probe_function) {
		struct mtd_info *mtd;

		mtd = (*probe_function)(map, primary);

		symbol_put_addr(probe_function);
		return mtd;
	}
#endif
	printk(KERN_NOTICE "Support for command set %04X not present\n", type);

	return NULL;
}
