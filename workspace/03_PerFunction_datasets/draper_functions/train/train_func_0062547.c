win_textbuffer_flow_break(window_textbuffer_t *dwin)
{
    while (dwin->ladjn || dwin->radjn)
        win_textbuffer_putchar_uni(dwin->owner, '\n');
    return TRUE;
}
