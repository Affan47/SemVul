vdrvwrite(int afd, int drive, int block)
{
    int i, err = 0, vfd = vdrvfd[drive];
    unsigned char block_buff[512];

    for (i = 0; i < 512; i++)
        read(afd, &block_buff[i], 1);
    if (vfd)
    {
        lseek(vfd, block * 512, 0);
        if (write(vfd, block_buff, 512) != 512)
            err = 0x27;
    }
    else
        err = 0x28;
    return err;
}
