check_inode_bitmap(int fd, unsigned int bg_num)
{
    unsigned int inode_bitmap_block_num;
    unsigned char block[MAX_EXT4_BLOCK_SIZE];
    int i, bitmap_updated = 0;


    inode_bitmap_block_num = aux_info.bg_desc[bg_num].bg_inode_bitmap;

    read_block(fd, inode_bitmap_block_num, block);

    for (i = info.inodes_per_group; i < new_inodes_per_group; i++) {
        if (bitmap_get_bit(block, i)) {
            bitmap_clear_bit(block, i);
            bitmap_updated = 1;
        }
    }

    if (bitmap_updated) {
        if (verbose) {
            printf("Warning: updated inode bitmap for block group %d\n", bg_num);
        }
        write_block(fd, inode_bitmap_block_num, block);
    }

    return;
}
