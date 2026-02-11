T_MoveCeiling(ceiling_t * ceiling)
{
    result_e res;

    switch (ceiling->direction)
    {
        case 0:
            break;
        case 1:
            res = T_MovePlane(ceiling->sector, ceiling->speed,
                              ceiling->topheight, false, 1,
                              ceiling->direction);
            if (!(leveltime & 7))
                S_StartSound(&ceiling->sector->soundorg,
                             sfx_dormov);
            if (res == pastdest)
                switch (ceiling->type)
                {
                    case raiseToHighest:
                        P_RemoveActiveCeiling(ceiling);
                        break;
                    case fastCrushAndRaise:
                    case crushAndRaise:
                        ceiling->direction = -1;
                        break;
                    default:
                        break;
                }
            break;
        case -1:
            res = T_MovePlane(ceiling->sector, ceiling->speed,
                              ceiling->bottomheight, ceiling->crush, 1,
                              ceiling->direction);
            if (!(leveltime & 7))
                S_StartSound(&ceiling->sector->soundorg,
                             sfx_dormov);
            if (res == pastdest)
                switch (ceiling->type)
                {
                    case crushAndRaise:
                        ceiling->speed = CEILSPEED;
                    case fastCrushAndRaise:
                        ceiling->direction = 1;
                        break;
                    case lowerAndCrush:
                    case lowerToFloor:
                        P_RemoveActiveCeiling(ceiling);
                        break;
                    default:
                        break;
                }
            else if (res == crushed)
                switch (ceiling->type)
                {
                    case crushAndRaise:
                    case lowerAndCrush:
                        ceiling->speed = CEILSPEED / 8;
                        break;
                    default:
                        break;
                }
            break;
    }
}
