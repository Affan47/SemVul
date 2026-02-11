morguemon(void)
{
    int i = rn2(100), hd = rn2(level_difficulty());

    if(hd > 10 && i < 10)
            return ((Inhell || In_endgame(&u.uz)) ? mkclass(S_DEMON,0) :
                    &mons[ndemon(A_NONE)]);
    if(hd > 8 && i > 85)
            return mkclass(S_VAMPIRE,0);

    return((i < 20) ? &mons[PM_GHOST]
           : (i < 40) ? &mons[PM_WRAITH] : mkclass(S_ZOMBIE,0));
}
