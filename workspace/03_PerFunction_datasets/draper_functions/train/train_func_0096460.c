delete_disk(struct aac_dev *dev, void __user *arg)
{
	struct aac_delete_disk dd;
	struct fsa_dev_info *fsa_dev_ptr;

	fsa_dev_ptr = dev->fsa_dev;
	if (!fsa_dev_ptr)
		return -EBUSY;

	if (copy_from_user(&dd, arg, sizeof (struct aac_delete_disk)))
		return -EFAULT;

	if (dd.cnum >= dev->maximum_num_containers)
		return -EINVAL;


	if (fsa_dev_ptr[dd.cnum].locked)
		return -EBUSY;
	else {


		fsa_dev_ptr[dd.cnum].valid = 0;
		fsa_dev_ptr[dd.cnum].devname[0] = '\0';
		return 0;
	}
}
