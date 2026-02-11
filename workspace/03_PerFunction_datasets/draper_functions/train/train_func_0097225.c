GifReadDimensions(FILE *file, DWORD *height, DWORD *width)
{
    BYTE buff[4];


    if(fseek(file, 6, SEEK_SET) != 0)
    {
        DEBUG_PRINT(("unable to seek to start of GIF file"));
        return FALSE;
    }


    if(fread(buff, 1, 4, file) != 4)
    {
        DEBUG_PRINT(("unable to read word from JFIF file"));
        return FALSE;
    }


    *width  = MAKE_WORD(buff[1], buff[0]);
    *height = MAKE_WORD(buff[3], buff[2]);
    return TRUE;
}
