iser_assign_reg_ops(struct iser_device *device)
{
	struct ib_device_attr *dev_attr = &device->dev_attr;


	if (device->ib_device->alloc_fmr && device->ib_device->dealloc_fmr &&
	    device->ib_device->map_phys_fmr && device->ib_device->unmap_fmr) {
		iser_info("FMR supported, using FMR for registration\n");
		device->reg_ops = &fmr_ops;
	} else
	if (dev_attr->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS) {
		iser_info("FastReg supported, using FastReg for registration\n");
		device->reg_ops = &fastreg_ops;
	} else {
		iser_err("IB device does not support FMRs nor FastRegs, can't register memory\n");
		return -1;
	}

	return 0;
}
