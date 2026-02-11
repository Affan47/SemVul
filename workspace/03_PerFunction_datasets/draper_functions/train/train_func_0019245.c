block_entry(xchar x, xchar y)
{
    xchar sx, sy;
    int roomno;
    struct monst *shkp;

    if(!(IS_DOOR(levl[u.ux][u.uy].typ) &&
         levl[u.ux][u.uy].doormask == D_BROKEN)) return false;

    roomno = *in_rooms(x, y, SHOPBASE);
    if(roomno < 0 || !IS_SHOP(roomno)) return false;
    if(!(shkp = shop_keeper((char)roomno)) || !inhishop(shkp))
            return false;

    if(ESHK(shkp)->shd.x != u.ux || ESHK(shkp)->shd.y != u.uy)
            return false;

    sx = ESHK(shkp)->shk.x;
    sy = ESHK(shkp)->shk.y;

    if(shkp->mx == sx && shkp->my == sy
       && shkp->mcanmove && !shkp->msleeping
       && (x == sx-1 || x == sx+1 || y == sy-1 || y == sy+1)
       && (Invis || carrying(PICK_AXE) || carrying(DWARVISH_MATTOCK)
           || u.usteed))
    {
        pline("%s%s blocks your way!", shkname(shkp),
              Invis ? " senses your motion and" : "");
        return true;
    }
    return false;
}
