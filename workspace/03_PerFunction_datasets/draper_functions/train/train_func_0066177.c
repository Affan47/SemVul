set_IVidx(unsigned char* packet)
{
    uchar ividx[4];

    if(packet == NULL) return 1;

    if(opt.prga == NULL && opt.crypt != CRYPT_WEP)
    {
        printf("Please specify a WEP key (-w).\n");
        return 1;
    }

    if( opt.crypt == CRYPT_WEP )
    {
        ividx[0] = rand() & 0xFF;
        ividx[1] = rand() & 0xFF;
        ividx[2] = rand() & 0xFF;
        ividx[3] = 0x00;
    }
    else if(opt.prga != NULL)
    {
        memcpy(ividx, opt.prga, 4);
    }


    memcpy(packet+24, ividx, 4);

    return 0;
}
