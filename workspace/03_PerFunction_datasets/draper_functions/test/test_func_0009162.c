getch(getc_type &tr)
{
    trace(("sub_getc()\n{\n"));
    wchar_t c = 0;
    for (;;)
    {
        c = getc_meta(tr);
        if (c && tr != getc_type_control)
            break;
        switch (c)
        {
        default:
            break;

        case 0:
            if (diversion_stack.empty())
                break;
            diversion_stack.pop_back();
            continue;

        case '$':
            if (!diversion_stack.resub_both())
                break;
            c = dollar();
            if (!c)
                continue;
            tr = getc_type_data;
            break;
        }
        break;
    }
#ifdef DEBUG
    if (iswprint(c) && c >= CHAR_MIN && c <= CHAR_MAX)
    {
        trace(("return '%c' %s;\n", (char)c,
            (tr == getc_type_control ? "control" : "data")));
    }
    else
    {
        trace(("return 0x%lX; /* %s */\n", (long)c,
            (tr == getc_type_control ? "control" : "data")));
    }
#endif
    trace(("}\n"));
    return c;
}
