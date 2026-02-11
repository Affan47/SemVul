getElement(const unsigned long num)
{
    errorFlag = EC_Normal;
    DcmElement *elem;
    elem = OFstatic_cast(DcmElement *, elementList->seek_to(num));

    if (elem == NULL)
        errorFlag = EC_IllegalCall;
    return elem;
}
