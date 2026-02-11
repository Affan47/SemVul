setDateTime(const OFDate &dateVal,
                               const OFTime &timeVal)
{
    const OFBool result = setDate(dateVal);

    return setTime(timeVal) && result;
}
