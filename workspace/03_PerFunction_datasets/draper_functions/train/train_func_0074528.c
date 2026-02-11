shop_keeper(char rmno)
{
    struct monst *shkp = rmno >= ROOMOFFSET ?
        rooms[rmno - ROOMOFFSET].resident : 0;

    if (shkp)
    {
        if (NOTANGRY(shkp))
        {
            if (ESHK(shkp)->surcharge) pacify_shk(shkp);
        }
        else
        {
            if (!ESHK(shkp)->surcharge) rile_shk(shkp);
        }
    }
    return shkp;
}
