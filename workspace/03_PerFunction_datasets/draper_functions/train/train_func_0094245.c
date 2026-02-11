AddEventToMultiTrack ( const MIDITimedMessage &msg, MIDISystemExclusive *sysex, int dest_track )
{
    bool result = false;

    if ( dest_track != -1 && dest_track < multitrack->GetNumTracks() )
    {
        MIDITrack *t = multitrack->GetTrack ( dest_track );

        if ( t )
        {
            result = t->PutEvent ( msg, sysex );
        }
    }

    return result;
}
