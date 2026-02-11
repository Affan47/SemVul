stripdot(string_ty *s)
{
    if (option.stripdot)
    {
        const char *cp = s->str_text;
        size_t len = s->str_length;
        while (len >= 2 && cp[0] == '.' && cp[1] == '/')
        {
            cp += 2;
            len -= 2;
            while (*cp == '/')
            {
                ++cp;
                --len;
            }
        }
        if (!len)
            return str_from_c(".");
        return str_n_from_c(cp, len);
    }
    else
        return str_copy(s);
}
