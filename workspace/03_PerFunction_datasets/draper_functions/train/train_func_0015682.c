boxGetSideLocation(BOX      *box,
                   l_int32   side,
                   l_int32  *ploc)
{
l_int32  x, y, w, h;

    PROCNAME("boxGetSideLocation");

    if (!ploc)
        return ERROR_INT("&loc not defined", procName, 1);
    *ploc = 0;
    if (!box)
        return ERROR_INT("box not defined", procName, 1);

    boxGetGeometry(box, &x, &y, &w, &h);
    if (side == L_GET_LEFT)
        *ploc = x;
    else if (side == L_GET_RIGHT)
        *ploc = x + w - 1;
    else if (side == L_GET_TOP)
        *ploc = y;
    else if (side == L_GET_BOT)
        *ploc = y + h - 1;
    else
        return ERROR_INT("invalid side", procName, 1);
    return 0;
}
