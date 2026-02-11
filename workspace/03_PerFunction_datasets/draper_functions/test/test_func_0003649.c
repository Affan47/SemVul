RaceTimePropose(GameTimer::tMsec inMsec)
{
    if (!RaceTimeValid() || inMsec < RaceTimeGet())
    {
        RaceTimeSet(inMsec);
    }
}
