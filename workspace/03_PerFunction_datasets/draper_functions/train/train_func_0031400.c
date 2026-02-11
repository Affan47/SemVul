writeToFile(XMLCSTR filename, const char *encoding, char nFormat) const
{
    if (!d) return eXMLErrorNone;
    FILE *f=xfopen(filename,_CXML("wb"));
    if (!f) return eXMLErrorCannotOpenWriteFile;
#ifdef _XMLWIDECHAR
    unsigned char h[2]={ 0xFF, 0xFE };
    if (!fwrite(h,2,1,f)) return eXMLErrorCannotWriteFile;
    if ((!isDeclaration())&&((d->lpszName)||(!getChildNode().isDeclaration())))
    {
        if (!fwrite(L"<?xml version=\"1.0\" encoding=\"utf-16\"?>\n",sizeof(wchar_t)*40,1,f))
            return eXMLErrorCannotWriteFile;
    }
#else
    if ((!isDeclaration())&&((d->lpszName)||(!getChildNode().isDeclaration())))
    {
        if (characterEncoding==char_encoding_UTF8)
        {

            unsigned char h[3]={0xEF,0xBB,0xBF}; if (!fwrite(h,3,1,f)) return eXMLErrorCannotWriteFile;
            encoding="utf-8";
        } else if (characterEncoding==char_encoding_ShiftJIS) encoding="SHIFT-JIS";

        if (!encoding) encoding="ISO-8859-1";
        if (fprintf(f,"<?xml version=\"1.0\" encoding=\"%s\"?>\n",encoding)<0) return eXMLErrorCannotWriteFile;
    } else
    {
        if (characterEncoding==char_encoding_UTF8)
        {
            unsigned char h[3]={0xEF,0xBB,0xBF}; if (!fwrite(h,3,1,f)) return eXMLErrorCannotWriteFile;
        }
    }
#endif
    int i;
    XMLSTR t=createXMLString(nFormat,&i);
    if (!fwrite(t,sizeof(XMLCHAR)*i,1,f)) return eXMLErrorCannotWriteFile;
    if (fclose(f)!=0) return eXMLErrorCannotWriteFile;
    free(t);
    return eXMLErrorNone;
}
