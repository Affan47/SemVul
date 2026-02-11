cvt_sdoor_to_door(struct rm *lev)
{
    int newmask = lev->doormask & ~WM_MASK;

#ifdef REINCARNATION
    if (Is_rogue_level(&u.uz))
    {

        newmask = D_NODOOR;
    }
    else
#endif
    {

        if (!(newmask & D_LOCKED))
        {
            newmask |= D_CLOSED;
        }
    }
    lev->typ = DOOR;
    lev->doormask = newmask;
}
