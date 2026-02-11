find_next_block(vfile *vf, union block *blk)
{
    int res;

    res = av_read(vf, blk->buffer, BLOCKSIZE);
    if(res <= 0)
        return res;
    if(res < BLOCKSIZE) {
        av_log(AVLOG_WARNING, "TAR: Broken archive");
        return -EIO;
    }

    return 1;
}
