mraid_mm_get_adapter(mimd_t __user *umimd, int *rval)
{
	mraid_mmadp_t	*adapter;
	mimd_t		mimd;
	uint32_t	adapno;
	int		iterator;


	if (copy_from_user(&mimd, umimd, sizeof(mimd_t))) {
		*rval = -EFAULT;
		return NULL;
	}

	adapno = GETADAP(mimd.ui.fcs.adapno);

	if (adapno >= adapters_count_g) {
		*rval = -ENODEV;
		return NULL;
	}

	adapter = NULL;
	iterator = 0;

	list_for_each_entry(adapter, &adapters_list_g, list) {
		if (iterator++ == adapno) break;
	}

	if (!adapter) {
		*rval = -ENODEV;
		return NULL;
	}

	return adapter;
}
