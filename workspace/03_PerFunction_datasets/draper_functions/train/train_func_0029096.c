contract_win_y(Client *c)
{
    if (!c || c->height <= WMDELTA)
        return;
    c->height -= WMDELTA;
    resize(c, 1);
}
