ParseSeek(long offset, int whence)
{
        int result = mame_fseek(fp, offset, whence);

        if (0 == result)
        {
                dwFilePos = mame_ftell(fp);
        }
        return (UINT8)result;
}
