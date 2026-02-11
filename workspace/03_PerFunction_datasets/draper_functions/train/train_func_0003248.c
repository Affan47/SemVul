shop_object(xchar x, xchar y)
{
    struct obj *otmp;
    struct monst *shkp;

    if(!(shkp = shop_keeper(*in_rooms(x, y, SHOPBASE))) || !inhishop(shkp))
            return NULL;

    for (otmp = level.objects[x][y]; otmp; otmp = otmp->nexthere)
            if (otmp->oclass != COIN_CLASS)
                    break;

    return (otmp && costly_spot(x, y) && NOTANGRY(shkp)
            && shkp->mcanmove && !shkp->msleeping)
        ? otmp : NULL;
}
