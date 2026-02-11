gfs2_check_magic(struct buffer_head *bh)
{
	void *kaddr;
	__be32 *ptr;

	clear_buffer_escaped(bh);
	kaddr = kmap_atomic(bh->b_page);
	ptr = kaddr + bh_offset(bh);
	if (*ptr == cpu_to_be32(GFS2_MAGIC))
		set_buffer_escaped(bh);
	kunmap_atomic(kaddr);
}
