PrintMsg ( FILE *f, MIDIMessage *m )
{
    int l = m->GetLength();
    fprintf ( f, "Msg : " );

    if ( l == 1 )
    {
        fprintf ( f, " %02x \t=", m->GetStatus() );
    }

    else if ( l == 2 )
    {
        fprintf ( f, " %02x %02x \t=", m->GetStatus(), m->GetByte1() );
    }

    else if ( l == 3 )
    {
        fprintf ( f, " %02x %02x %02x \t=", m->GetStatus(), m->GetByte1(), m->GetByte2() );
    }

    char buf[129];
    m->MsgToText ( buf );
    fprintf ( f, "%s\n", buf );
    fflush ( f );
}
