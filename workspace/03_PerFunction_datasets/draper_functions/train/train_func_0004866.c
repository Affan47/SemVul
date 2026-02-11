diMount(struct inode *ipimap)
{
	struct inomap *imap;
	struct metapage *mp;
	int index;
	struct dinomap_disk *dinom_le;


	imap = kmalloc(sizeof(struct inomap), GFP_KERNEL);
	if (imap == NULL) {
		jfs_err("diMount: kmalloc returned NULL!");
		return -ENOMEM;
	}


	mp = read_metapage(ipimap,
			   IMAPBLKNO << JFS_SBI(ipimap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	if (mp == NULL) {
		kfree(imap);
		return -EIO;
	}


	dinom_le = (struct dinomap_disk *) mp->data;
	imap->im_freeiag = le32_to_cpu(dinom_le->in_freeiag);
	imap->im_nextiag = le32_to_cpu(dinom_le->in_nextiag);
	atomic_set(&imap->im_numinos, le32_to_cpu(dinom_le->in_numinos));
	atomic_set(&imap->im_numfree, le32_to_cpu(dinom_le->in_numfree));
	imap->im_nbperiext = le32_to_cpu(dinom_le->in_nbperiext);
	imap->im_l2nbperiext = le32_to_cpu(dinom_le->in_l2nbperiext);
	for (index = 0; index < MAXAG; index++) {
		imap->im_agctl[index].inofree =
		    le32_to_cpu(dinom_le->in_agctl[index].inofree);
		imap->im_agctl[index].extfree =
		    le32_to_cpu(dinom_le->in_agctl[index].extfree);
		imap->im_agctl[index].numinos =
		    le32_to_cpu(dinom_le->in_agctl[index].numinos);
		imap->im_agctl[index].numfree =
		    le32_to_cpu(dinom_le->in_agctl[index].numfree);
	}


	release_metapage(mp);


	IAGFREE_LOCK_INIT(imap);


	for (index = 0; index < MAXAG; index++) {
		AG_LOCK_INIT(imap, index);
	}


	imap->im_ipimap = ipimap;
	JFS_IP(ipimap)->i_imap = imap;

	return (0);
}
