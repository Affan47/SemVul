line_number_of_character_at_offset(size_t offset)
{


    const wchar_t *str = orig_buff;
    if (! str)
        return 0;


    if (offset == 0)
        return 1;

    size_t i;
    if (offset > cached_lineno_offset)
    {
        for (i = cached_lineno_offset; str[i] && i<offset; i++)
        {

            if (str[i] == L'\n')
                cached_lineno_count++;
        }
        cached_lineno_offset = i;
    }
    else if (offset < cached_lineno_offset)
    {

        for (i = offset; i < cached_lineno_offset; i++)
        {
            if (str[i] == L'\n')
                cached_lineno_count--;
        }
        cached_lineno_offset = offset;
    }
    return cached_lineno_count + 1;
}
