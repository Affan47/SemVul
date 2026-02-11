OnRoundEnd()
{

    if ( Alive() && player )
    {
        Player()->AddScore( score_survive, tOutput("$player_win_survive"), tOutput() );
    }
}
