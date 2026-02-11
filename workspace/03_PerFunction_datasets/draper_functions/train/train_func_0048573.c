read_archive_header(vfile *vf)
{
    int res;
    block_header main_head;
    avuint crc;
    avbyte tmpbuf[6];
    int headlen;

    headlen = read_block_header(vf, main_head, 1);
    if(headlen < 0)
        return headlen;

    if (bh_type(main_head) != B_MAIN) {
        av_log(AVLOG_ERROR, "URAR: Bad archive header");
        return -EIO;
    }

    crc = CRC_string(CRC_START, main_head + 2, headlen - 2);


    res = av_read_all(vf, (char*)tmpbuf, 6);
    if(res < 0)
        return res;
    crc = CRC_string(crc, tmpbuf, 6);

    if ((avushort)~crc != bh_CRC(main_head)) {
        av_log(AVLOG_ERROR, "URAR: Bad archive header CRC");
        return -EIO;
    }

    av_lseek(vf, bh_size(main_head) - headlen - 6, AVSEEK_CUR);

    return 0;
}
