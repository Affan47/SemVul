updateDiskStat( void )
{
    DiskInfo *disk_info;
    FILE *fh;
    struct mntent *mnt_info;

    if ( ( fh = setmntent( "/etc/mtab", "r" ) ) == NULL ) {
        print_error( "Cannot open \'/etc/mtab\'!\n" );
        return -1;
    }
    if(OldDiskStatList == 0) {
        OldDiskStatList = DiskStatList;
        DiskStatList = new_ctnr();
    } else {
        empty_ctnr(DiskStatList);
    }

    while ( ( mnt_info = getmntent( fh ) ) != NULL ) {


        if ( (mnt_info->mnt_fsname[0] != '/') ||
             !strcmp( mnt_info->mnt_type, "smbfs" ) ||
             !strcmp( mnt_info->mnt_type, "cifs" ) ||
             !strcmp( mnt_info->mnt_type, "proc" ) ||
             !strcmp( mnt_info->mnt_type, "devfs" ) ||
             !strcmp( mnt_info->mnt_type, "usbfs" ) ||
             !strcmp( mnt_info->mnt_type, "sysfs" ) ||
             !strcmp( mnt_info->mnt_type, "tmpfs" ) ||
             !strcmp( mnt_info->mnt_type, "devpts" ) )
            continue;

        if ( ( disk_info = (DiskInfo *)malloc( sizeof( DiskInfo ) ) ) == NULL )
            continue;

        memset( disk_info, 0, sizeof( DiskInfo ) );

        if ( statvfs( mnt_info->mnt_dir, &(disk_info->statvfs) ) < 0 )
            continue;

        strncpy( disk_info->device, mnt_info->mnt_fsname, sizeof( disk_info->device ) );
        disk_info->device[ sizeof(disk_info->device) -1] = 0;

        strncpy( disk_info->mntpnt, mnt_info->mnt_dir, sizeof( disk_info->mntpnt ) );
        disk_info->mntpnt[ sizeof(disk_info->mntpnt) - 1] = 0;
        sanitize(disk_info->mntpnt);

        push_ctnr( DiskStatList, disk_info );
    }
    endmntent( fh );

    return 0;
}
