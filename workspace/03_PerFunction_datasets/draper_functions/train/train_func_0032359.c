pxe_fs_init(struct fs_info *fs)
{
    (void)fs;


    fs->sector_shift = fs->block_shift = TFTP_BLOCKSIZE_LG2;
    fs->sector_size  = fs->block_size  = 1 << TFTP_BLOCKSIZE_LG2;


    fs->sector_shift = fs->block_shift = TFTP_BLOCKSIZE_LG2;
    fs->sector_size  = fs->block_size  = 1 << TFTP_BLOCKSIZE_LG2;


    if (pxe_init(false))
	kaboom();


    gpxe_init();


    network_init();


    pxe_idle_init();


    strcpy(fs->cwd_name, "::");

    return 0;
}
