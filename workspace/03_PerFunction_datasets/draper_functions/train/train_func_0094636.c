T_MoveCeiling(ceiling_t * ceiling)
{
    result_e res;

    switch (ceiling->direction)
    {


        case 1:
            res = T_MovePlane(ceiling->sector, ceiling->speed,
                              ceiling->topheight, false, 1,
                              ceiling->direction);
            if (res == RES_PASTDEST)
            {
                SN_StopSequence((mobj_t *) & ceiling->sector->soundorg);
                switch (ceiling->type)
                {
                    case CLEV_CRUSHANDRAISE:
                        ceiling->direction = -1;
                        ceiling->speed = ceiling->speed * 2;
                        break;
                    default:
                        P_RemoveActiveCeiling(ceiling);
                        break;
                }
            }
            break;
        case -1:
            res = T_MovePlane(ceiling->sector, ceiling->speed,
                              ceiling->bottomheight, ceiling->crush, 1,
                              ceiling->direction);
            if (res == RES_PASTDEST)
            {
                SN_StopSequence((mobj_t *) & ceiling->sector->soundorg);
                switch (ceiling->type)
                {
                    case CLEV_CRUSHANDRAISE:
                    case CLEV_CRUSHRAISEANDSTAY:
                        ceiling->direction = 1;
                        ceiling->speed = ceiling->speed / 2;
                        break;
                    default:
                        P_RemoveActiveCeiling(ceiling);
                        break;
                }
            }
            else if (res == RES_CRUSHED)
            {
                switch (ceiling->type)
                {
                    case CLEV_CRUSHANDRAISE:
                    case CLEV_LOWERANDCRUSH:
                    case CLEV_CRUSHRAISEANDSTAY:

                        break;
                    default:
                        break;
                }
            }
            break;
    }
}
