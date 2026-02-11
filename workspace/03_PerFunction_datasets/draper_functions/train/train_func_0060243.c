checkForOctalConversion(const OFString &sourceString,
                                           const size_t maxLength)
{
    OFBool result = OFFalse;
    size_t pos = 0;
    const size_t strLen = sourceString.length();

    const size_t length = (maxLength == 0) ? strLen : ((strLen < maxLength) ? strLen : maxLength);

    while (pos < length)
    {
        const size_t c = OFstatic_cast(unsigned char, sourceString.at(pos));
        if ((c < 32) || (c >= 127))
        {

            result = OFTrue;
            break;
        }
        ++pos;
    }
    return result;
}
