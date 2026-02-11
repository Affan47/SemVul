gru_read_gpa(unsigned long *value, unsigned long gpa)
{
	void *cb;
	void *dsr;
	int ret, iaa;

	STAT(read_gpa);
	if (gru_get_cpu_resources(GRU_NUM_KERNEL_DSR_BYTES, &cb, &dsr))
		return MQE_BUG_NO_RESOURCES;
	iaa = gpa >> 62;
	gru_vload_phys(cb, gpa, gru_get_tri(dsr), iaa, IMA);
	ret = gru_wait(cb);
	if (ret == CBS_IDLE)
		*value = *(unsigned long *)dsr;
	gru_free_cpu_resources(cb, dsr);
	return ret;
}
