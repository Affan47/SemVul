kgd_address_watch_disable(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	union TCP_WATCH_CNTL_BITS cntl;
	unsigned int i;

	cntl.u32All = 0;

	cntl.bitfields.valid = 0;
	cntl.bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;
	cntl.bitfields.atc = 1;


	for (i = 0; i < MAX_WATCH_ADDRESSES; i++)
		WREG32(watchRegs[i * ADDRESS_WATCH_REG_MAX +
			ADDRESS_WATCH_REG_CNTL], cntl.u32All);

	return 0;
}
