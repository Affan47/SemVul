checkStringValue(const OFString &value,
                                          const OFString &charset)
{
    return DcmByteString::checkStringValue(value, "" , "lt", 14, 0 , charset);
}
