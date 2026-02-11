efreet_xml_text_parse(char **data, int *size, const char **text)
{
    const char *start = NULL, *end = NULL;
    int buf_size;


    while (*size > 0)
    {
        if (!isspace(**data))
        {
            start = *data;
            break;
        }
        (*size)--;
        (*data)++;
    }

    if (!start) return;


    while (*size > 0)
    {
        if (**data == '<')
        {
            end = *data;
            break;
        }
        (*size)--;
        (*data)++;
    }
    if (!end) return;


    while (isspace(*(end - 1))) end--;


    buf_size = end - start + 1;
    if (buf_size <= 1) return;

    *text = eina_stringshare_add_length(start, buf_size - 1);
}
