continueGame()
{
    if ((mCurrentGameState != GameState_Stop) && mStandbyFlag)
    {
        mStandbyFlag = false;

        mGameStartTime = getMillisecOfNow();
    }

    return mCurrentGameState;
}
