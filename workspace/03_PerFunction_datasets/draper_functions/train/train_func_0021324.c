get_the_right_sector(struct file *file)
{
    struct inode *inode = file->inode;
    uint32_t sector_pos  = file->offset >> SECTOR_SHIFT(file->fs);
    uint32_t where;
    sector_t sector;

    if (sector_pos < PVT(inode)->offset) {

	where = 0;
	sector = PVT(inode)->start;
    } else {
	where = PVT(inode)->offset;
	sector = PVT(inode)->here;
    }

    while (where < sector_pos) {
	sector = get_next_sector(file->fs, sector);
	where++;
    }

    PVT(inode)->offset = sector_pos;
    PVT(inode)->here   = sector;

    return sector;
}
