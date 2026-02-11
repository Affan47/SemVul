selectSubString(long charnum, long nchars, ExceptionCode& ec) const
{
    long numberOfChars = getNumberOfChars();
    if (charnum < 0 || nchars < 0 || charnum > numberOfChars) {
        ec = DOMException::INDEX_SIZE_ERR;
        return;
    }

    if (nchars > numberOfChars - charnum)
        nchars = numberOfChars - charnum;

    ASSERT(document());


}
