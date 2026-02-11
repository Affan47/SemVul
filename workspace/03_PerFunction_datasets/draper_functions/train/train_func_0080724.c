exitDiskStat( void )
{
    DiskInfo* disk_info;

    removeMonitor( "partitions/list" );

    for ( disk_info = first_ctnr( DiskStatList ); disk_info; disk_info = next_ctnr( DiskStatList ) ) {
        removeMonitors(disk_info->mntpnt);
    }

    destr_ctnr( DiskStatList, free );
    if(OldDiskStatList)
        destr_ctnr( OldDiskStatList, free );
}
