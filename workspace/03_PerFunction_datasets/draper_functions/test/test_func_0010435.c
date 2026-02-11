mark_FAT_sector(int sector, unsigned int value)
{
    int cluster;

    cluster = (sector - start_data_sector) / (int)(bs.cluster_size) /
	(sector_size / HARD_SECTOR_SIZE);
    if (cluster < 0)
	die("Invalid cluster number in mark_FAT_sector: probably bug!");

    mark_FAT_cluster(cluster, value);
}
