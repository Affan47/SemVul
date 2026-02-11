gfs2_get_leaf_nr(struct gfs2_inode *dip, uint32_t lindex,
		      uint64_t *leaf_out)
{
	uint64_t leaf_no;
	int count;

	count = gfs2_readi(dip, (char *)&leaf_no, lindex * sizeof(uint64_t),
			   sizeof(uint64_t));
	if (count != sizeof(uint64_t)) {
		fprintf(stderr, "gfs2_get_leaf_nr:  Bad internal read.\n");
		exit(1);
	}

	*leaf_out = be64_to_cpu(leaf_no);
}
