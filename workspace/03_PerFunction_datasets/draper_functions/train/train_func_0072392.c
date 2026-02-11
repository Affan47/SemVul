parse_util_cmdsubst_extent(const wchar_t *buff,
                                size_t cursor_pos,
                                const wchar_t **a,
                                const wchar_t **b)
{
    wchar_t *begin, *end;
    wchar_t *pos;
    const wchar_t *cursor = buff + cursor_pos;

    CHECK(buff,);

    if (a)
    {
        *a = (wchar_t *)buff;
    }

    if (b)
    {
        *b = (wchar_t *)buff+wcslen(buff);
    }

    pos = (wchar_t *)buff;

    while (1)
    {
        if (parse_util_locate_cmdsubst(pos,
                                       &begin,
                                       &end,
                                       1) <= 0)
        {


            break;
        }

        if (!end)
        {
            end = (wchar_t *)buff + wcslen(buff);
        }

        if ((begin < cursor) && (end >= cursor))
        {
            begin++;

            if (a)
            {
                *a = begin;
            }

            if (b)
            {
                *b = end;
            }

            break;
        }

        if (!*end)
        {
            break;
        }

        pos = end+1;
    }

}
