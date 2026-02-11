block_door(xchar x, xchar y)
{
    int roomno = *in_rooms(x, y, SHOPBASE);
    struct monst *shkp;

    if(roomno < 0 || !IS_SHOP(roomno)) return false;
    if(!IS_DOOR(levl[x][y].typ)) return false;
    if(roomno != *u.ushops) return false;

    if(!(shkp = shop_keeper((char)roomno)) || !inhishop(shkp))
            return false;

    if(shkp->mx == ESHK(shkp)->shk.x && shkp->my == ESHK(shkp)->shk.y


       && ESHK(shkp)->shd.x == x && ESHK(shkp)->shd.y == y
       && shkp->mcanmove && !shkp->msleeping
       && (ESHK(shkp)->debit || ESHK(shkp)->billct ||
           ESHK(shkp)->robbed))
    {
        pline("%s%s blocks your way!", shkname(shkp),
              Invis ? " senses your motion and" : "");
        return true;
    }
    return false;
}
