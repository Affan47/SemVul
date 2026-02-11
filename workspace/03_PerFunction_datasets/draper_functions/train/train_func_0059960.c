UpdateMusicCRC(uint16_t * crc, unsigned char *buffer, int size)
{
    int     i;
    for (i = 0; i < size; ++i)
        *crc = CRC_update_lookup(buffer[i], *crc);
}
