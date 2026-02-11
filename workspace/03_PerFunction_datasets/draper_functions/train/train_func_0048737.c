getRand(const uint64_t size)
{

    int randFile_fd = 0;
    uint8_t* randomData = NULL;
    if(exists(HWRNG))
    {
        randFile_fd = openForRead(HWRNG);
        if(randFile_fd < 0)
        {
            fprintf(stderr, "Unable to open %s cannot continue\n", HWRNG);
            return NULL;
        }
    }
    else if(exists(PSRNG))
    {
        randFile_fd = openForRead(PSRNG);
        if(randFile_fd < 0)
        {
            fprintf(stderr, "Unable to open %s cannot continue\n", PSRNG);
            return NULL;
        }
    }

    randomData = readBytes(size, randFile_fd);
    close(randFile_fd);

    return randomData;
}
