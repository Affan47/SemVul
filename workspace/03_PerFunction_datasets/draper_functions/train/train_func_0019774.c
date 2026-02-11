T_MovePlane
( sector_t*     sector,
 fixed_t        speed,
 fixed_t        dest,
 boolean        crush,
 int            floorOrCeiling,
 int            direction )
{
    boolean     flag;
    fixed_t     lastpos;

    switch(floorOrCeiling)
    {
    case 0:

        switch(direction)
        {
        case -1:

            if (sector->floorheight - speed < dest)
            {


                sector->floorheight = dest;
                flag = P_ChangeSector(sector,crush);


                return pastdest;
            }
            else
            {


                sector->floorheight -= speed;
                flag = P_ChangeSector(sector,crush);


                return ok;
             }
             break;

        case 1:

            if (sector->floorheight + speed > dest)
            {
                lastpos = sector->floorheight;
                sector->floorheight = dest;
                flag = P_ChangeSector(sector,crush);
                if (flag == true)
                {
                    sector->floorheight = lastpos;
                    P_ChangeSector(sector,crush);

                }
                return pastdest;
            }
            else
            {

                lastpos = sector->floorheight;
                sector->floorheight += speed;
                flag = P_ChangeSector(sector,crush);
                if (flag == true)
                {

                    if (crush == true)
                        return crushed;
                    sector->floorheight = lastpos;
                    P_ChangeSector(sector,crush);
                    return crushed;
                }
                else
                    return ok;
            }
            break;
        }
        break;

    case 1:

        switch(direction)
        {
        case -1:

            if (sector->ceilingheight - speed < dest)
            {
                lastpos = sector->ceilingheight;
                sector->ceilingheight = dest;
                flag = P_ChangeSector(sector,crush);

                if (flag == true)
                {
                    sector->ceilingheight = lastpos;
                    P_ChangeSector(sector,crush);

                }
                return pastdest;
            }
            else
            {

                lastpos = sector->ceilingheight;
                sector->ceilingheight -= speed;
                flag = P_ChangeSector(sector,crush);

                if (flag == true)
                {
                    if (crush == true)
                        return crushed;
                    sector->ceilingheight = lastpos;
                    P_ChangeSector(sector,crush);
                    return crushed;
                }
            }
            break;

        case 1:

            if (sector->ceilingheight + speed > dest)
            {


                sector->ceilingheight = dest;


                return pastdest;
            }
            else
            {


                sector->ceilingheight += speed;


                return ok;
            }
            break;
        }
        break;

    }
    return ok;
}
