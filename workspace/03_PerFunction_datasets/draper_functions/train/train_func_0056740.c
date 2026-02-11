Silence_conf(std::istream &s)
{
    if ( se_NeedsServer( "SILENCE", s ) )
    {
        return;
    }

    ePlayerNetID * p = ReadPlayer( s );
    if ( p && !p->IsSilenced() )
    {
        sn_ConsoleOut( tOutput( "$player_silenced", p->GetColoredName() ) );
        p->SetSilenced( true );
    }
}
