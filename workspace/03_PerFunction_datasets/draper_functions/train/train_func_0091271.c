wil_pmc_llseek(struct file *filp, loff_t off, int whence)
{
	loff_t newpos;
	struct wil6210_priv *wil = filp->private_data;
	struct pmc_ctx *pmc = &wil->pmc;
	size_t pmc_size = pmc->descriptor_size * pmc->num_descriptors;

	switch (whence) {
	case 0:
		newpos = off;
		break;

	case 1:
		newpos = filp->f_pos + off;
		break;

	case 2:
		newpos = pmc_size;
		break;

	default:
		return -EINVAL;
	}

	if (newpos < 0)
		return -EINVAL;
	if (newpos > pmc_size)
		newpos = pmc_size;

	filp->f_pos = newpos;

	return newpos;
}
