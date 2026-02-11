se_BuildChatString( eTeam const *team, ePlayerNetID const *sender, tString const &message )
{
    tColoredString console;
    console << *sender;

    if( !team )
    {

        console << tColoredString::ColorString(1,1,.5) << " --> " << tOutput("$player_spectator_message");
    }
    else if (sender->CurrentTeam() == team)
    {

        console << tColoredString::ColorString(1,1,.5) << " --> ";

        console << tColoredString::ColorString( team->R() / 15.0, team->G() / 15.0, team->B() / 15.0 ) << tOutput("$player_team_message");
    }
    else {

        eTeam *senderTeam = sender->CurrentTeam();
        console << tColoredString::ColorString(1,1,.5) << " (";
        console << *senderTeam;
        console << tColoredString::ColorString(1,1,.5) << ") --> ";
        console << *team;
    }

    console << tColoredString::ColorString(1,1,.5) << ": ";
    se_AppendChat( console, message );

    return console;
}
