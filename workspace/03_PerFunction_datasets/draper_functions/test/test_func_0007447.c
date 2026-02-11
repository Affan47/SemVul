ok_align(int rolenum, int racenum, int gendnum, int alignnum)
{
    int i;
    short allow;

    if (alignnum >= 0 && alignnum < ROLE_ALIGNS)
    {
        allow = aligns[alignnum].allow;
        if (rolenum >= 0 && rolenum < SIZE(roles)-1 &&
            !(allow & roles[rolenum].allow & ROLE_ALIGNMASK))
                return false;
        if (racenum >= 0 && racenum < SIZE(races)-1 &&
            !(allow & races[racenum].allow & ROLE_ALIGNMASK))
                return false;
        return true;
    }
    else
    {
        for (i = 0; i < ROLE_ALIGNS; i++)
        {
            allow = races[i].allow;
            if (rolenum >= 0 && rolenum < SIZE(roles)-1 &&
                !(allow & roles[rolenum].allow & ROLE_ALIGNMASK))
                    continue;
            if (racenum >= 0 && racenum < SIZE(races)-1 &&
                !(allow & races[racenum].allow & ROLE_ALIGNMASK))
                    continue;
            return true;
        }
        return false;
    }
}
