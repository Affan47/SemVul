WaitToLeaveChat()
{
    static bool lastReturn = false;
    static double lastTime = 0;
    static ePlayerNetID * lastPlayer = 0;
    double time = tSysTimeFloat();
    REAL dt = time - lastTime;
    bool ret = false;

    if ( !lastReturn )
    {

        for ( int i = se_PlayerNetIDs.Len()-1; i>=0; --i )
        {
            ePlayerNetID* player = se_PlayerNetIDs(i);
            if ( dt > 1.0 || !player->chatting_ )
            {
                player->wait_ += se_playerWaitFraction * dt;
                if ( player->wait_ > se_playerWaitMax )
                {
                    player->wait_ = se_playerWaitMax;
                }
            }
        }

        if ( dt > 1.0 )
            lastPlayer = 0;

        dt = 0;
    }


    ePlayerNetID * maxPlayer = 0;
    REAL maxWait = .2;


    for ( int i = se_PlayerNetIDs.Len()-1; i>=0; --i )
    {
        ePlayerNetID* player = se_PlayerNetIDs(i);
        if ( player->CurrentTeam() && !player->IsSilenced() && player->chatting_ && ( !se_playerWaitTeamleader || player->CurrentTeam()->OldestHumanPlayer() == player ) )
        {

            if ( !se_playerWaitSingle )
            {
                player->wait_ -= dt;


                if ( player->wait_ > 0 )
                {
                    ret = true;
                }
                else
                {
                    player->wait_ = 0;
                }
            }


            if (  ( maxPlayer != lastPlayer || NULL == maxPlayer ) && ( player->wait_ > maxWait || player == lastPlayer ) && player->wait_ > 0 )
            {
                maxWait = player->wait_;
                maxPlayer = player;
            }
        }
    }


    if ( se_playerWaitSingle && maxPlayer )
    {
        maxPlayer->wait_ -= dt;


        if ( maxPlayer->wait_ < 0 )
        {
            maxPlayer->wait_ = 0;
        }
    }

    static double lastPrint = -2;


    if ( maxPlayer && maxPlayer != lastPlayer && tSysTimeFloat() - lastPrint > 1 )
    {
        sn_ConsoleOut( tOutput( "$gamestate_chat_wait", maxPlayer->GetName(), int(10*maxPlayer->wait_)*.1f ) );
        lastPlayer = maxPlayer;
    }

    if ( lastPlayer == maxPlayer )
    {
        lastPrint = tSysTimeFloat();
    }


    lastReturn = ret;
    lastTime = time;

    return ret;
}
