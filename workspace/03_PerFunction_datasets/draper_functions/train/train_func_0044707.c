wstring_list_to_wstring(wstring_list_ty *wl, int start, int stop, char *sep)
{
    size_t          j;
    size_t          k;
    static wchar_t  *tmp;
    static size_t   tmplen;
    size_t          length;
    size_t          seplen;
    wchar_t         *pos;
    wstring_ty      *s;

    if (!sep)
        sep = " ";
    seplen = strlen(sep);
    length = 0;
    for (j = start; (int)j <= stop && j < wl->nitems; ++j)
    {
        s = wl->item[j];
        if (s->wstr_length)
        {
            if (length)
                length += seplen;
            length += s->wstr_length;
        }
    }

    if (tmplen < length)
    {
        tmplen = length;
        tmp = mem_change_size(tmp, tmplen * sizeof(wchar_t));
    }

    pos = tmp;
    for (j = start; (int)j <= stop && j < wl->nitems; j++)
    {
        s = wl->item[j];
        if (s->wstr_length)
        {
            if (pos != tmp)
            {
                for (k = 0; k < seplen; ++k)
                    *pos++ = sep[k];
            }
            memcpy(pos, s->wstr_text, s->wstr_length * sizeof(wchar_t));
            pos += s->wstr_length;
        }
    }

    s = wstr_n_from_wc(tmp, length);
    return s;
}
