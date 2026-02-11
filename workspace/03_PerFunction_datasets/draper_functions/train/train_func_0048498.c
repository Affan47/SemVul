wrapper_VSIFWriteL( int nLen, char *pBuf, int size, int memb, VSILFILE * f)
{
    if (nLen < size * memb)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "Inconsistent buffer size with 'size' and 'memb' values");
        return 0;
    }
    return VSIFWriteL(pBuf, size, memb, f);
}
