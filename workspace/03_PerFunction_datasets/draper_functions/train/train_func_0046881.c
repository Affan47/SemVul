parseRes(Formattable& res,
         const   UNumberFormat*  fmt,
         const   UChar*          text,
         int32_t         textLength,
         int32_t         *parsePos ,
         UErrorCode      *status)
{
    if(U_FAILURE(*status))
        return;

    const UnicodeString src((UBool)(textLength == -1), text, textLength);
    ParsePosition pp;

    if(parsePos != 0)
        pp.setIndex(*parsePos);

    ((const NumberFormat*)fmt)->parse(src, res, pp);

    if(pp.getErrorIndex() != -1) {
        *status = U_PARSE_ERROR;
        if(parsePos != 0) {
            *parsePos = pp.getErrorIndex();
        }
    } else if(parsePos != 0) {
        *parsePos = pp.getIndex();
    }
}
