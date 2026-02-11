root_distance(struct super_block *sb, gc_level_t __gc_level)
{
	struct logfs_super *super = logfs_super(sb);
	u8 gc_level = (__force u8)__gc_level;

	switch (gc_level) {
	case 0:
	case 1:
	case 2:
	case 3:

		return super->s_ifile_levels + super->s_iblock_levels - gc_level;
	case 6:
	case 7:
	case 8:
	case 9:

		return super->s_ifile_levels - (gc_level - 6);
	default:
		printk(KERN_ERR"LOGFS: segment of unknown level %x found\n",
				gc_level);
		WARN_ON(1);
		return super->s_ifile_levels + super->s_iblock_levels;
	}
}
