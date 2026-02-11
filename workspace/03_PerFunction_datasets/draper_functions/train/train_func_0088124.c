s_write_ps_string(stream * s, const byte * str, uint size, int print_ok)
{
    uint added = 0;
    uint i;
    const stream_template *templat;
    stream_AXE_state state;
    stream_state *st = NULL;

    if (print_ok & PRINT_BINARY_OK) {

        stream_putc(s, '(');
        for (i = 0; i < size; ++i) {
            byte ch = str[i];

            switch (ch) {
                case char_CR:
                    stream_puts(s, "\\r");
                    continue;
                case char_EOL:
                    stream_puts(s, "\\n");
                    continue;
                case '(':
                case ')':
                case '\\':
                    stream_putc(s, '\\');
            }
            stream_putc(s, ch);
        }
        stream_putc(s, ')');
        return;
    }
    for (i = 0; i < size; ++i) {
        byte ch = str[i];

        if (ch == 0 || ch >= 127)
            added += 3;
        else if (strchr("()\\\n\r\t\b\f", ch) != 0)
            ++added;
        else if (ch < 32)
            added += 3;
    }

    if (added < size || (print_ok & PRINT_HEX_NOT_OK)) {

        templat = &s_PSSE_template;
        stream_putc(s, '(');
    } else {

        templat = &s_AXE_template;
        st = (stream_state *) & state;
        s_AXE_init_inline(&state);
        stream_putc(s, '<');
    }

    {
        byte buf[100];
        stream_cursor_read r;
        stream_cursor_write w;
        int status;

        r.ptr = str - 1;
        r.limit = r.ptr + size;
        w.limit = buf + sizeof(buf) - 1;
        do {

            w.ptr = buf;  w.ptr--;
            status = (*templat->process) (st, &r, &w, true);
            stream_write(s, buf, (uint) (w.ptr + 1 - buf));
        }
        while (status == 1);
    }
}
