format(const Formattable& obj,
                   UnicodeString& appendTo,
                   FieldPosition& pos,
                   UErrorCode& status) const
{
    switch (obj.getType())
    {
    case Formattable::kString:
        return format(obj.getString(), appendTo, pos, status);
    default:
        if( U_SUCCESS(status) ){
            status = U_ILLEGAL_ARGUMENT_ERROR;
        }
        return appendTo;
    }
}
