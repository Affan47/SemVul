check_magic_numbers(exec_options *eo, file_state *fs, uint8_t *block, off_t off) {
    if ( memcmp("\x53\xEF", block+56, 2) == 0 )
        check_ext(eo, fs, off);

    if ( memcmp("SWAPSPACE2", block+512-10, 10) == 0 )
        check_linuxswap(eo, fs, off);

    if ( memcmp("\x54\x19\x01\x00", block+348, 4) == 0 )
        check_ffs(eo, fs, off);
    if ( memcmp("\x19\x01\x54\x19", block+348, 4) == 0 )
        check_ffs(eo, fs, off);

    if ( memcmp("ReIsErFs", block+0x34, 8) == 0 )
        check_reiserfs(eo, fs, off);
    if ( memcmp("ReIsEr2Fs", block+0x34, 9) == 0 )
        check_reiserfs(eo, fs, off);
    if ( memcmp("ReIsEr3Fs", block+0x34, 9) == 0 )
        check_reiserfs(eo, fs, off);

    if ( memcmp("_BHRfS_M", block+0x40, 8) == 0 )
        check_btrfs(eo, fs, off);

    if ( memcmp("NTFS    ", block+0x03, 8) == 0 )
        check_ntfs(eo, fs, off);

    if ( memcmp("\x55\xAA", block+0x1FE, 2) == 0 )
        check_fat(eo, fs, off);

    if ( memcmp("H+", block, 2) == 0 )
        check_hfsplus(eo, fs, off);
    if ( memcmp("HX", block, 2) == 0 )
        check_hfsplus(eo, fs, off);
}
