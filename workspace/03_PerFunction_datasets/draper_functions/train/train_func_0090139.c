emit_char(int c)
{
    if (!icol && !ocol)
        icol = 8 * depth;
    if (back_slash_seen && (c == ' ' || c == '\\'))
    {
        assert(icol == ocol);
        back_slash_seen = 0;
        goto normal;
    }
    back_slash_seen = (c == '\\');
    switch (c)
    {
    case ' ':
        ++icol;
        return;

    case '\t':
        icol = (icol + 8) & ~7;
        return;

    case '\n':
        if (putc(c, output) == EOF)
            goto bomb;
        icol = 0;
        ocol = 0;
        ++old_ln;
        return;
    }
  normal:
    while (((ocol + 8) & ~7) <= icol && ocol + 1 < icol)
    {
        if (putc('\t', output) == EOF)
            goto bomb;
        ocol = (ocol + 8) & ~7;
    }
    while (ocol < icol)
    {
        if (putc(' ', output) == EOF)
            goto bomb;
        ++ocol;
    }
    if (putc(c, output) == EOF)
    {
      bomb:
        fatal_intl_write(filename->str_text);
    }
    ++icol;
    ++ocol;
}
