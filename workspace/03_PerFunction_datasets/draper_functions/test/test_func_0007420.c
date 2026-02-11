P_ShootSpecialLine
( mobj_t*       thing,
  line_t*       line )
{
    int         ok;


    if (!thing->player)
    {
        ok = 0;
        switch(line->special)
        {
        case 46:
        case 182:
            ok = 1;
            break;
        }
        if (!ok)
            return;
    }

    switch(line->special)
    {
    case 24:

        EV_DoFloor(line,raiseFloor);
        P_ChangeSwitchTexture(line,0);
        break;

    case 46:

        EV_DoDoor(line,open);
        P_ChangeSwitchTexture(line,1);
        break;

    case 47:


        EV_DoPlat(line,raiseToNearestAndChange,0);
        P_ChangeSwitchTexture(line,0);
        break;

    case 180:

        EV_DoFloor(line, raiseFloor512AndChange);
        P_ChangeSwitchTexture(line, 0);
        break;

    case 182:


        P_ChangeSwitchTexture(line, 0);
        break;
    }
}
