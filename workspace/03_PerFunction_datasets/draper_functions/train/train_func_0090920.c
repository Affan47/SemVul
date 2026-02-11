right(el_status_t Change)
{
    tty_show(rl_line_buffer[rl_point]);

    if (Change == CSmove)
        rl_point++;
}
