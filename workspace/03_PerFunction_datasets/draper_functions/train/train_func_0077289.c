cow_write(BlockDriverState *bs, int64_t sector_num,
                     const uint8_t *buf, int nb_sectors)
{
    BDRVCowState *s = bs->opaque;
    int ret, i;

    lseek(s->fd, s->cow_sectors_offset + sector_num * 512, SEEK_SET);
    ret = write(s->fd, buf, nb_sectors * 512);
    if (ret != nb_sectors * 512)
        return -1;
    for (i = 0; i < nb_sectors; i++)
        cow_set_bit(s->cow_bitmap, sector_num + i);
    return 0;
}
