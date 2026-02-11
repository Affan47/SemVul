set_item_state(winid window, int lineno, tty_menu_item *item)
{
    char ch = item->selected ? (item->count == -1L ? '+' : '#') : '-';
    tty_curs(window, 4, lineno);
    term_start_attr(item->attr);
    putchar(ch);
    ttyDisplay->curx++;
    term_end_attr(item->attr);
}
