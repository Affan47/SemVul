unzlocal_getShort (pzlib_filefunc_def,filestream,pX)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
    uLong *pX;
{
    uLong x ;
    int err;
    int i = 0;

    err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
    x = (uLong)i;

    if (err==UNZ_OK)
        err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<8;

    if (err==UNZ_OK)
        *pX = x;
    else
        *pX = 0;
    return err;
}
