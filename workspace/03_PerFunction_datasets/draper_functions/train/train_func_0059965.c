SetPlayer(ePlayerNetID* a_player)
{
    tASSERT( !a_player || Owner() == player->Owner() );
    player  = a_player;
    if ( laggometerSmooth == 0 && sn_GetNetState() != nCLIENT )
        laggometerSmooth = laggometer = se_GetPing( player );
}
