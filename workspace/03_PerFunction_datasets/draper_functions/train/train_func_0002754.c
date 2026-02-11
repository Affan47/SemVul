DataSourceFseek(long offset, int origin)
{
    if (origin == SEEK_CUR && offset < 0)
        return VSIFSeekL(fp, VSIFTellL(fp) + offset, SEEK_SET);
    else
        return VSIFSeekL(fp, offset, origin);
}
