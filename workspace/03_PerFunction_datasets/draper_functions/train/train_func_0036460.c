chip_intel_8042_n_reset_set(void *_css, unsigned int n_val)
{
	struct cpssp *cpssp = (struct cpssp *) _css;

	if (! n_val) {
		kbc_reset(cpssp);
	}
}
