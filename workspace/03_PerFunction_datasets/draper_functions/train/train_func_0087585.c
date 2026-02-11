M_EndGame(int choice)
{
    choice = 0;
    if (!usergame)
    {
        S_StartSound(NULL,sfx_oof);
        return;
    }

    if (netgame)
    {
        M_StartMessage(DEH_String(NETEND),NULL,false);
        return;
    }

    M_StartMessage(DEH_String(ENDGAME),M_EndGameResponse,true);
}
