first_sector(struct fs_info *fs,
				    const struct fat_dir_entry *dir)
{
    const struct fat_sb_info *sbi = FAT_SB(fs);
    sector_t first_clust;
    sector_t sector;

    first_clust = (dir->first_cluster_high << 16) + dir->first_cluster_low;
    if (first_clust == 0)
	sector = sbi->root;
    else
	sector = ((first_clust - 2) << sbi->clust_shift) + sbi->data;

    return sector;
}
