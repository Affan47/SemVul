unzlocal_SearchCentralDir64(const zlib_filefunc_def* pzlib_filefunc_def,
                                      voidpf filestream)
{
    unsigned char* buf;
    uLong64 uSizeFile;
    uLong64 uBackRead;
    uLong64 uMaxBack=0xffff;
    uLong64 uPosFound=0;
    uLong uL;

    if (ZSEEK(*pzlib_filefunc_def,filestream,0,ZLIB_FILEFUNC_SEEK_END) != 0)
        return 0;


    uSizeFile = ZTELL(*pzlib_filefunc_def,filestream);

    if (uMaxBack>uSizeFile)
        uMaxBack = uSizeFile;

    buf = (unsigned char*)ALLOC(BUFREADCOMMENT+4);
    if (buf==NULL)
        return 0;

    uBackRead = 4;
    while (uBackRead<uMaxBack)
    {
        uLong uReadSize;
        uLong64 uReadPos;
        int i;
        if (uBackRead+BUFREADCOMMENT>uMaxBack)
            uBackRead = uMaxBack;
        else
            uBackRead+=BUFREADCOMMENT;
        uReadPos = uSizeFile-uBackRead ;

        uReadSize = ((BUFREADCOMMENT+4) < (uSizeFile-uReadPos)) ?
                     (BUFREADCOMMENT+4) : (uLong)(uSizeFile-uReadPos);
        if (ZSEEK(*pzlib_filefunc_def,filestream,uReadPos,ZLIB_FILEFUNC_SEEK_SET)!=0)
            break;

        if (ZREAD(*pzlib_filefunc_def,filestream,buf,uReadSize)!=uReadSize)
            break;

        for (i=(int)uReadSize-3; (i--)>0;)
            if (((*(buf+i))==0x50) && ((*(buf+i+1))==0x4b) &&
                ((*(buf+i+2))==0x06) && ((*(buf+i+3))==0x07))
            {
                uPosFound = uReadPos+i;
                break;
            }

        if (uPosFound!=0)
            break;
    }
    TRYFREE(buf);
    if (uPosFound == 0)
        return 0;


    if (ZSEEK(*pzlib_filefunc_def,filestream, uPosFound,ZLIB_FILEFUNC_SEEK_SET)!=0)
        return 0;


    if (unzlocal_getLong(pzlib_filefunc_def,filestream,&uL)!=UNZ_OK)
        return 0;


    if (unzlocal_getLong(pzlib_filefunc_def,filestream,&uL)!=UNZ_OK)
        return 0;
    if (uL != 0)
        return 0;


    uLong64 relativeOffset;
    if (unzlocal_getLong64(pzlib_filefunc_def,filestream,&relativeOffset)!=UNZ_OK)
        return 0;


    if (unzlocal_getLong(pzlib_filefunc_def,filestream,&uL)!=UNZ_OK)
        return 0;
    if (uL != 1)
        return 0;


    if (ZSEEK(*pzlib_filefunc_def,filestream, relativeOffset,ZLIB_FILEFUNC_SEEK_SET)!=0)
        return 0;


    if (unzlocal_getLong(pzlib_filefunc_def,filestream,&uL)!=UNZ_OK)
        return 0;

    if (uL != 0x06064b50)
        return 0;

    return relativeOffset;
}
