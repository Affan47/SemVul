printDiskStat( const char* cmd )
{
    DiskInfo* disk_info;

    (void)cmd;
    for ( disk_info = first_ctnr( DiskStatList ); disk_info; disk_info = next_ctnr( DiskStatList ) ) {

        unsigned long totalSizeKB =  disk_info->statvfs.f_blocks * (disk_info->statvfs.f_frsize/1024);
        unsigned long usedKB = totalSizeKB - (disk_info->statvfs.f_bfree * (disk_info->statvfs.f_bsize/1024));
        unsigned long available = disk_info->statvfs.f_bavail * (disk_info->statvfs.f_bsize/1024);
        int percentageUsed = calculatePercentageUsed(totalSizeKB, available);
        output( "%s\t%ld\t%ld\t%ld\t%d\t%s\n",
                disk_info->device,
                totalSizeKB,
                usedKB,
                available,
                percentageUsed,
                disk_info->mntpnt );
    }

    output( "\n" );
}
