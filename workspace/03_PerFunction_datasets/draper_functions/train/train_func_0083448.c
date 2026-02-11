is_bmp(FILE *fp)
{
    UINT8 marker[3];
    if (fread(marker, sizeof(UINT16), 2, fp) != 2)
        err_exit(FILE_READ_ERR);
    if (marker[0] != 0x42 || marker[1] != 0x4D)
        return false;
    rewind(fp);
    return true;
}
