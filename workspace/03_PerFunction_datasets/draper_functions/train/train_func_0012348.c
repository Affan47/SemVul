insert_string(const char *p)
{
    size_t      len;
    int         i;
    char        *line;
    char        *q;

    len = strlen(p);
    if (rl_end + len >= Length) {
	line = malloc(sizeof(char) * (Length + len + MEM_INC));
        if (!line)
            return CSstay;

        if (Length) {
            memcpy(line, rl_line_buffer, Length);
            free(rl_line_buffer);
        }

        rl_line_buffer = line;
        Length += len + MEM_INC;
    }

    for (q = &rl_line_buffer[rl_point], i = rl_end - rl_point; --i >= 0; )
        q[len + i] = q[i];

    memcpy(&rl_line_buffer[rl_point], p, len);
    rl_end += len;
    rl_line_buffer[rl_end] = '\0';
    tty_string(&rl_line_buffer[rl_point]);
    rl_point += len;

    return rl_point == rl_end ? CSstay : CSmove;
}
