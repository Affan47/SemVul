writeBMP(const char *filename,
                         const int bits,
                         const unsigned long frame)
{
    if ((filename != NULL) && (Image != NULL) &&
        ((bits == 0) || ((bits == 8) && isMonochrome()) || (bits == 24) || (bits == 32)))
    {
        char fname[FILENAME_MAX + 1];
        if (sprintf(fname, filename, frame) >= 0)
            filename = fname;
        FILE *stream = fopen(filename, "wb");
        if (stream != NULL)
        {
            int ok = Image->writeBMP(stream, frame, bits);
            fclose(stream);
            return ok;
        }
    }
    return 0;
}
