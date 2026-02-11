getFilenameFromPath(OFFilename &result,
                                            const OFFilename &pathName,
                                            const OFBool assumeFilename)
{
#if defined(WIDE_CHAR_FILE_IO_FUNCTIONS) && defined(_WIN32)

    if (pathName.usesWideChars())
    {
        const wchar_t *strValue = pathName.getWideCharPointer();
        const wchar_t *strPos = wcsrchr(strValue, L'\\' );

        if (strPos == NULL)
        {
            if (assumeFilename)
                result = pathName;
            else
                result.clear();
        } else {
            wchar_t *tmpString = new wchar_t[wcslen(strPos)];
            wcscpy(tmpString, strPos + 1);
            result.set(tmpString, OFTrue );
            delete[] tmpString;
        }
    } else
#endif

    {
        const char *strValue = pathName.getCharPointer();
        const char *strPos = strrchr(strValue, PATH_SEPARATOR);

        if (strPos == NULL)
        {
            if (assumeFilename)
                result = pathName;
            else
                result.clear();
        } else
            result.set(OFString(strPos + 1));
    }
    return result;
}
