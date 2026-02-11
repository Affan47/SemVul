inode_is_in_use(struct dinode *inode_ptr, uint32_t inode_num)
{
	int iiiu_result;
	int ixpxd_unequal = 0;

	ixpxd_unequal =
	    memcmp((void *) &(inode_ptr->di_ixpxd),
		   (void *) &(agg_recptr->ino_ixpxd), sizeof (pxd_t));

	iiiu_result = ((inode_ptr->di_inostamp == agg_recptr->inode_stamp)
		       && (inode_ptr->di_number == inode_num)
		       && (inode_ptr->di_fileset == agg_recptr->ino_fsnum)
		       && (!ixpxd_unequal) && (inode_ptr->di_nlink != 0));

	return (iiiu_result);
}
