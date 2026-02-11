part4(DATA * drop)
{
    mvaddch(drop->y - 1, drop->x, '-');
    mvaddstr(drop->y, drop->x - 1, "|.|");
    mvaddch(drop->y + 1, drop->x, '-');
}
