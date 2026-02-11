CheckForPushSpecial(line_t * line, int side, mobj_t * mobj)
{
    if (line->special)
    {
        if (mobj->flags2 & MF2_PUSHWALL)
        {
            P_ActivateLine(line, mobj, side, SPAC_PUSH);
        }
        else if (mobj->flags2 & MF2_IMPACT)
        {
            P_ActivateLine(line, mobj, side, SPAC_IMPACT);
        }
    }
}
