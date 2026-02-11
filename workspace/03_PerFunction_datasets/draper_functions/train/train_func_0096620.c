GDALPipeWrite_internal(GDALPipe* p, const void* data, int length)
{
    if(!p->bOK)
        return FALSE;
    if( p->fout != CPL_FILE_INVALID_HANDLE )
    {
        int nRet = CPLPipeWrite(p->fout, data, length);
        if( !nRet )
        {
            CPLError(CE_Failure, CPLE_AppDefined, "Write to pipe failed");
            p->bOK = FALSE;
        }
        return nRet;
    }
    else
    {
        const char* pabyData = (const char*) data;
        int nRemain = length;
        while( nRemain > 0 )
        {
            int nRet = send(p->nSocket, pabyData, nRemain, 0);
            if( nRet < 0 )
            {
                CPLError(CE_Failure, CPLE_AppDefined, "Write to socket failed");
                p->bOK = FALSE;
                return FALSE;
            }
            pabyData += nRet;
            nRemain -= nRet;
        }
        return TRUE;
    }
}
