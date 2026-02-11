vxfs_bmap_typed(struct inode *ip, long iblock)
{
	struct vxfs_inode_info		*vip = VXFS_INO(ip);
	daddr_t				pblock = 0;
	int				i;

	for (i = 0; i < VXFS_NTYPED; i++) {
		struct vxfs_typed	*typ = vip->vii_org.typed + i;
		int64_t			off = (typ->vt_hdr & VXFS_TYPED_OFFSETMASK);

#ifdef DIAGNOSTIC
		vxfs_typdump(typ);
#endif
		if (iblock < off)
			continue;
		switch ((u_int32_t)(typ->vt_hdr >> VXFS_TYPED_TYPESHIFT)) {
		case VXFS_TYPED_INDIRECT:
			pblock = vxfs_bmap_indir(ip, typ->vt_block,
					typ->vt_size, iblock - off);
			if (pblock == -2)
				break;
			return (pblock);
		case VXFS_TYPED_DATA:
			if ((iblock - off) < typ->vt_size)
				return (typ->vt_block + iblock - off);
			break;
		case VXFS_TYPED_INDIRECT_DEV4:
		case VXFS_TYPED_DATA_DEV4: {
			struct vxfs_typed_dev4	*typ4 =
				(struct vxfs_typed_dev4 *)typ;

			printk(KERN_INFO "\n\nTYPED_DEV4 detected!\n");
			printk(KERN_INFO "block: %Lu\tsize: %Ld\tdev: %d\n",
			       (unsigned long long) typ4->vd4_block,
			       (unsigned long long) typ4->vd4_size,
			       typ4->vd4_dev);
			return 0;
		}
		default:
			BUG();
		}
	}

	return 0;
}
