write_float(float val)
{
    if (useBinary)
    {
        force_big_endian((unsigned char *) &val);
        fwrite(&val, sizeof(float), 1, fp);
    }
    else
    {
        fprintf(fp, "%20.12e ", val);
        if (((numInColumn++) % 9) == 8)
        {
            end_line();
        }
    }
}
