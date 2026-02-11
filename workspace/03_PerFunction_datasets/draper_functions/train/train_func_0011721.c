addGamePlayer(GamePlayerInterface * p, int thinkInterval, int processInterval)
{
    if (mPlayerCount == mMaxCapacity)
    {
        return false;
    }
    maPlayerList[mPlayerCount] = new KBlocksSinglePlayer(p, thinkInterval, processInterval);
    mPlayerCount++;
    return true;
}
