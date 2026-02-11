GetEvent ( int event_num, MIDITimedBigMessage *msg ) const
{
    if ( !IsValidEventNum( event_num ) )
    {
        return false;
    }
    else
    {
        msg->Copy ( *GetEventAddress ( event_num ) );
        return true;
    }
}
