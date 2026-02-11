nilfs_cpfile_do_get_ssinfo(struct inode *cpfile, __u64 *cnop,
					  void *buf, unsigned cisz, size_t nci)
{
	struct buffer_head *bh;
	struct nilfs_cpfile_header *header;
	struct nilfs_checkpoint *cp;
	struct nilfs_cpinfo *ci = buf;
	__u64 curr = *cnop, next;
	unsigned long curr_blkoff, next_blkoff;
	void *kaddr;
	int n = 0, ret;

	down_read(&NILFS_MDT(cpfile)->mi_sem);

	if (curr == 0) {
		ret = nilfs_cpfile_get_header_block(cpfile, &bh);
		if (ret < 0)
			goto out;
		kaddr = kmap_atomic(bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
		curr = le64_to_cpu(header->ch_snapshot_list.ssl_next);
		kunmap_atomic(kaddr);
		brelse(bh);
		if (curr == 0) {
			ret = 0;
			goto out;
		}
	} else if (unlikely(curr == ~(__u64)0)) {
		ret = 0;
		goto out;
	}

	curr_blkoff = nilfs_cpfile_get_blkoff(cpfile, curr);
	ret = nilfs_cpfile_get_checkpoint_block(cpfile, curr, 0, &bh);
	if (unlikely(ret < 0)) {
		if (ret == -ENOENT)
			ret = 0;
		goto out;
	}
	kaddr = kmap_atomic(bh->b_page);
	while (n < nci) {
		cp = nilfs_cpfile_block_get_checkpoint(cpfile, curr, bh, kaddr);
		curr = ~(__u64)0;
		if (unlikely(nilfs_checkpoint_invalid(cp) ||
			     !nilfs_checkpoint_snapshot(cp)))
			break;
		nilfs_cpfile_checkpoint_to_cpinfo(cpfile, cp, ci);
		ci = (void *)ci + cisz;
		n++;
		next = le64_to_cpu(cp->cp_snapshot_list.ssl_next);
		if (next == 0)
			break;

		next_blkoff = nilfs_cpfile_get_blkoff(cpfile, next);
		if (curr_blkoff != next_blkoff) {
			kunmap_atomic(kaddr);
			brelse(bh);
			ret = nilfs_cpfile_get_checkpoint_block(cpfile, next,
								0, &bh);
			if (unlikely(ret < 0)) {
				WARN_ON(ret == -ENOENT);
				goto out;
			}
			kaddr = kmap_atomic(bh->b_page);
		}
		curr = next;
		curr_blkoff = next_blkoff;
	}
	kunmap_atomic(kaddr);
	brelse(bh);
	*cnop = curr;
	ret = n;

 out:
	up_read(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}
