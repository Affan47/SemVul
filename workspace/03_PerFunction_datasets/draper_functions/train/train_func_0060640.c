GetBytes()
{

#ifdef POPPLER_BASE_STREAM_HAS_TWO_ARGS
    GooString* gstr = new GooString();
    m_poStream->fillGooString(gstr);

    if( gstr->getLength() )
    {
        m_nLength = gstr->getLength();
        char* pszContent = (char*) VSIMalloc(m_nLength + 1);
        if (!pszContent)
            return NULL;
        memcpy(pszContent, gstr->getCString(), m_nLength);
        pszContent[m_nLength] = '\0';
        delete gstr;
        return pszContent;
    }
    else
    {
        delete gstr;
        return NULL;
    }
#else
    int i;
    int nLengthAlloc = 0;
    char* pszContent = NULL;
    if( m_nLength >= 0 )
    {
        pszContent = (char*) VSIMalloc(m_nLength + 1);
        if (!pszContent)
            return NULL;
        nLengthAlloc = m_nLength;
    }
    m_poStream->reset();
    for(i = 0; ; ++i )
    {
        int nVal = m_poStream->getChar();
        if (nVal == EOF)
            break;
        if( i >= nLengthAlloc )
        {
            nLengthAlloc = 32 + nLengthAlloc + nLengthAlloc / 3;
            char* pszContentNew = (char*) VSIRealloc(pszContent, nLengthAlloc + 1);
            if( pszContentNew == NULL )
            {
                CPLFree(pszContent);
                m_nLength = 0;
                return NULL;
            }
            pszContent = pszContentNew;
        }
        pszContent[i] = (GByte)nVal;
    }
    m_nLength = i;
    pszContent[i] = '\0';
    return pszContent;
#endif
}
