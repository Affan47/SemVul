own_game( nNetState enter_state ){
    tNEW(gGame);
    se_MakeGameTimer();
    max_player_speed = 0.0;
    sg_EnterGame( enter_state );


    ePlayerNetID::LogScoreDifferences();
    ePlayerNetID::UpdateSuspensions();
    ePlayerNetID::UpdateShuffleSpamTesters();
    sg_gameEndWriter.write();

    sg_currentGame=NULL;
    se_KillGameTimer();
}
