Clear()
{
    ENTER ( "MIDIMatrix::Clear()" );

    for ( int channel = 0; channel < 16; ++channel )
    {
        ClearChannel ( channel );
    }

    total_count = 0;
}
