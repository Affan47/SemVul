cb_intel_eepro100_c0r(void *_cpss, uint32_t addr, unsigned int bs, uint32_t *valp)
{
	struct cpssp *cpssp = (struct cpssp *) _cpss;

	if ((addr >> 11) & 1) {
		return sig_pci_bus_idsel_c0r(cpssp->sig_idsel, cpssp,
				addr, bs, valp);
	} else {
		return -1;
	}
}
