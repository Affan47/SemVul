bk_word(void)
{
    int         i;
    char        *p;

    i = 0;
    do {
        for (p = &rl_line_buffer[rl_point]; p > rl_line_buffer && !is_alpha_num(p[-1]); p--)
            left(CSmove);

        for (; p > rl_line_buffer && !isblank(p[-1]) && is_alpha_num(p[-1]); p--)
            left(CSmove);

        if (rl_point == 0)
            break;
    } while (++i < Repeat);

    return CSstay;
}
