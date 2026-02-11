RemoveIdenticalEvents( int max_distance_between_identical_events )
{
    int removed = 0;

    for ( int n = 0; n < num_events; ++n )
    {
        MIDITimedBigMessage *mn = GetEvent( n );

        for (int i = 1; i < max_distance_between_identical_events; ++i)
        {
            if ( (n+i) >= num_events )
                break;

            MIDITimedBigMessage *mni = GetEvent( n+i );
            if ( *mn == *mni )
            {
                ++removed;
                MakeEventNoOp( n );
                break;
            }
        }
    }

    return removed;
}
