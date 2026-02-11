PngFormatFound(FILE *file)
{
    BYTE header[8];


    if(fseek(file, 0, SEEK_SET) != 0)
    {
        DEBUG_PRINT(("unable to seek to start of PNG file"));
        return FALSE;
    }


    if(fread(header, 1, 8, file) != 8)
    {
        DEBUG_PRINT(("could not read PNG image file header"));
        return FALSE;
    }


    if(memcmp(header, "\211PNG\r\n\032\n", 8) == 0)
    {
        if(fseek(file, 12, SEEK_SET) != 0)
        {
            DEBUG_PRINT(("unable to seek to IHDR block of PNG file"));
            return FALSE;
        }

        if(fread(header, 1, 4, file) != 4)
        {
            DEBUG_PRINT(("could not read PNG image IHDR signature"));
            return FALSE;
        }

        if(memcmp(header, "IHDR", 4) == 0)
        {

            return TRUE;
        }
    }


    return FALSE;
}
