move_win_left(Client *c)
{
    if (!c)
        return;
    c->x -= WMDELTA;
    move(c, 1);
}
