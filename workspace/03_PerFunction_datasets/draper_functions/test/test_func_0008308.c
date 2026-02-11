VSIGIFWriteFunc( GifFileType *psGFile,
                            const GifByteType *pabyBuffer, int nBytesToWrite )

{
    VSILFILE* fp = (VSILFILE *) psGFile->UserData;
    if ( VSIFTellL(fp) == 0 && nBytesToWrite >= 6 &&
         memcmp(pabyBuffer, "GIF87a", 6) == 0 )
    {


        int nRet = VSIFWriteL("GIF89a", 1, 6, fp);
        nRet += VSIFWriteL( (char *) pabyBuffer + 6, 1, nBytesToWrite - 6, fp );
        return nRet;
    }
    else
        return VSIFWriteL( (void *) pabyBuffer, 1, nBytesToWrite, fp );
}
