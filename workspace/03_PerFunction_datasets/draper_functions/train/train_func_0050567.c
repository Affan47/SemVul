convertToMarkupString(const OFString &sourceString,
                                                  OFString &markupString,
                                                  const OFBool convertNonASCII,
                                                  const E_MarkupMode markupMode,
                                                  const OFBool newlineAllowed)
{
    OFStringStream stream;

    if (OFStandard::convertToMarkupStream(stream, sourceString, convertNonASCII, markupMode, newlineAllowed).good())
    {
        stream << OFStringStream_ends;

        OFSTRINGSTREAM_GETSTR(stream, buffer_str)
        markupString.assign(buffer_str);
        OFSTRINGSTREAM_FREESTR(buffer_str)
    } else
        markupString.clear();
    return markupString;
}
