reposition(void)
{
    int i;

    tty_put('\r');
    tty_puts(rl_prompt);
    for (i = 0; i < rl_point; i++)
        tty_show(rl_line_buffer[i]);
}
