format(const Formattable& obj,
                   UnicodeString& appendTo,
                   FieldPosition& pos,
                   UErrorCode& status) const
{
    if (U_FAILURE(status)) return appendTo;
    int32_t number;

    switch (obj.getType())
    {
    case Formattable::kDouble:
        return format((int32_t)obj.getDouble(), appendTo, pos, status);
        break;
    case Formattable::kLong:
        number = (int32_t)obj.getLong();
        return format(number, appendTo, pos, status);
        break;
    case Formattable::kInt64:
        return format((int32_t)obj.getInt64(), appendTo, pos, status);
    default:
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return appendTo;
    }
}
