F_CastTicker (void)
{
    int         st;

    if (--casttics > 0)
        return;

    if (caststate->tics == -1 || caststate->nextstate == S_NULL)
    {

        castnum++;
        castdeath = false;
        if (isdemoversion)
        {

            if(!castorder[castnum].isindemo)
                castnum = 0;
        }

        if (castorder[castnum].type == NUMMOBJTYPES)
            castnum = 0;
        if (mobjinfo[castorder[castnum].type].seesound)
            S_StartSound (NULL, mobjinfo[castorder[castnum].type].seesound);
        caststate = &states[mobjinfo[castorder[castnum].type].seestate];
        castframes = 0;
    }
    else
    {
        int sfx = 0;


        if (caststate == &states[S_PLAY_05])
            goto stopattack;
        st = caststate->nextstate;
        caststate = &states[st];
        castframes++;

        if (st != mobjinfo[castorder[castnum].type].meleestate &&
            st != mobjinfo[castorder[castnum].type].missilestate)
        {
            if (st == S_PLAY_05)
                sfx = sfx_rifle;
            else
                sfx = 0;
        }
        else
            sfx = mobjinfo[castorder[castnum].type].attacksound;

        if (sfx)
            S_StartSound (NULL, sfx);
    }

    if (!castdeath && castframes == 12)
    {

        castattacking = true;
        if (castonmelee)
            caststate=&states[mobjinfo[castorder[castnum].type].meleestate];
        else
            caststate=&states[mobjinfo[castorder[castnum].type].missilestate];
        castonmelee ^= 1;
        if (caststate == &states[S_NULL])
        {
            if (castonmelee)
                caststate = &states[mobjinfo[castorder[castnum].type].meleestate];
            else
                caststate = &states[mobjinfo[castorder[castnum].type].missilestate];
        }
    }

    if (castattacking)
    {
        if (castframes == 24
            ||	caststate == &states[mobjinfo[castorder[castnum].type].seestate] )
        {
stopattack:
            castattacking = false;
            castframes = 0;
            caststate = &states[mobjinfo[castorder[castnum].type].seestate];
        }
    }

    casttics = caststate->tics;
    if (casttics > 50)
        casttics = 50;
    else if (casttics == -1)
        casttics = 15;
}
