aac_fib_vector_assign(struct aac_dev *dev)
{
	u32 i = 0;
	u32 vector = 1;
	struct fib *fibptr = NULL;

	for (i = 0, fibptr = &dev->fibs[i];
		i < (dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB);
		i++, fibptr++) {
		if ((dev->max_msix == 1) ||
		  (i > ((dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB - 1)
			- dev->vector_cap))) {
			fibptr->vector_no = 0;
		} else {
			fibptr->vector_no = vector;
			vector++;
			if (vector == dev->max_msix)
				vector = 1;
		}
	}
}
