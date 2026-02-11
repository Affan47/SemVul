GetRealGameNo(const uint no) const
{
    int realno = 1;
    if (no > 0)
    {
        realno = no % mGameNos[GAME_NOS_CNT - 1][0];
    }
    return realno;
}
