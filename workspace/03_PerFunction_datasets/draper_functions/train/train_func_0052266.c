diReadSpecial(struct super_block *sb, ino_t inum, int secondary)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	uint address;
	struct dinode *dp;
	struct inode *ip;
	struct metapage *mp;

	ip = new_inode(sb);
	if (ip == NULL) {
		jfs_err("diReadSpecial: new_inode returned NULL!");
		return ip;
	}

	if (secondary) {
		address = addressPXD(&sbi->ait2) >> sbi->l2nbperpage;
		JFS_IP(ip)->ipimap = sbi->ipaimap2;
	} else {
		address = AITBL_OFF >> L2PSIZE;
		JFS_IP(ip)->ipimap = sbi->ipaimap;
	}

	ASSERT(inum < INOSPEREXT);

	ip->i_ino = inum;

	address += inum >> 3;


	mp = read_metapage(ip, address << sbi->l2nbperpage, PSIZE, 1);
	if (mp == NULL) {
		set_nlink(ip, 1);
		iput(ip);
		return (NULL);
	}


	dp = (struct dinode *) (mp->data);
	dp += inum % 8;


	if ((copy_from_dinode(dp, ip)) != 0) {

		set_nlink(ip, 1);
		iput(ip);

		release_metapage(mp);
		return (NULL);

	}

	ip->i_mapping->a_ops = &jfs_metapage_aops;
	mapping_set_gfp_mask(ip->i_mapping, GFP_NOFS);


	ip->i_flags |= S_NOQUOTA;

	if ((inum == FILESYSTEM_I) && (JFS_IP(ip)->ipimap == sbi->ipaimap)) {
		sbi->gengen = le32_to_cpu(dp->di_gengen);
		sbi->inostamp = le32_to_cpu(dp->di_inostamp);
	}


	release_metapage(mp);


	hlist_add_fake(&ip->i_hash);

	return (ip);
}
