restore_symbol(char *out, char *in)
{
    int  len;

    len = strlen(in);
    if (len > 0)
    {
        if ((len == 1 && in[0] == ormark) ||
            (in[0] == escape)             ||
            (in[0] == '\'')               ||
            (in[len - 1] == '\'')         ||
            (strchr(in, ' ') != NULL &&
            (in[0] != '<' || in[len - 1] != '>')))
        {
            *(out++) = '\'';
            while(*in != '\0')
            {
                if (*in == '\'')
                    *(out++) = *in;
                *(out++) = *(in++);
            }
            *(out++) = '\'';
            *out = '\0';

            return;
        }
    }

    strcpy(out, in);

    if (out[0] == '\n')
        out[0] = escape;

    return;
}
