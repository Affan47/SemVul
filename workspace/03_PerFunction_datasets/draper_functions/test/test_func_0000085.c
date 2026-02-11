getBestTwoPlayersState (const Player &leftCharacter,
                                         const Player &rightCharacter)
{
    IState *twoPlayersState = 0;
    if ( leftCharacter.isComputerPlayer && rightCharacter.isComputerPlayer )
    {
        twoPlayersState =
            new TwoComputerPlayersState (leftCharacter.computerPlayerLevel,
                                         rightCharacter.computerPlayerLevel,
                                         this);
    }
#if defined (IS_GP2X_HOST)
    else if ( !leftCharacter.isComputerPlayer &&
              !rightCharacter.isComputerPlayer )
    {
        twoPlayersState =
            new TwoGP2XPlayersState (
                    AIPlayerFactory::getRandomBackgroundFileName (),
                    leftCharacter.score, rightCharacter.score, this);
    }
#endif
    else
    {
        IPlayer *leftPlayer = getMatchPlayer (leftCharacter, IPlayer::LeftSide);
        IPlayer *rightPlayer = getMatchPlayer (rightCharacter, IPlayer::RightSide);
        twoPlayersState =
            new TwoPlayersState (leftPlayer, rightPlayer,
                                 AIPlayerFactory::getRandomBackgroundFileName (),
                                 leftCharacter.score, rightCharacter.score,
                                 this);
    }

    return twoPlayersState;
}
