findKeyword(const UnicodeString& s,
                                   const UChar * const *list)
{
    if (s.length() == 0)
        return 0;

    UnicodeString buffer = s;


    buffer.trim().toLower("");
    for (int32_t i = 0; list[i]; ++i) {
        if (!buffer.compare(list[i], u_strlen(list[i]))) {
            return i;
        }
    }
    return -1;
}
