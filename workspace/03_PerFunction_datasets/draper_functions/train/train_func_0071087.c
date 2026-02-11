get_next_sector(struct fs_info* fs, uint32_t sector)
{
    struct fat_sb_info *sbi = FAT_SB(fs);
    sector_t data_area = sbi->data;
    sector_t data_sector;
    uint32_t cluster;
    int clust_shift = sbi->clust_shift;

    if (sector < data_area) {

	sector++;
	if (sector >= data_area)
	    sector = 0;
	return sector;
    }

    data_sector = sector - data_area;
    if ((data_sector + 1) & sbi->clust_mask)
	return sector + 1;


    cluster = data_sector >> clust_shift;
    cluster = get_next_cluster(fs, cluster + 2) - 2;

    if (cluster >= sbi->clusters)
	return 0;


    sector = (cluster << clust_shift) + data_area;
    return sector;
}
