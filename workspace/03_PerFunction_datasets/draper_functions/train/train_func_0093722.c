Invite( ePlayerNetID * player )
{
    tASSERT( player );
    if ( !IsInvited( player ) && this->IsLocked() )
    {
	sn_ConsoleOut( tOutput( "$invite_team_can_join", player->GetColoredName(), Name() ) );
    }
    else if ( !IsInvited( player ) )
    {
        sn_ConsoleOut( tOutput( "$invite_team_invite", player->GetColoredName(), Name() ) );
    }
    player->invitations_.insert( this );
}
