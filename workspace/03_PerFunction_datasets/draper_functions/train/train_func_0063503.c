main ( int argc, char **argv )
{
    if ( argc > 1 )
    {
        MIDIFileReadStreamFile rs ( argv[1] );
        MIDIMultiTrack tracks ( 64 );
        MIDIFileReadMultiTrack track_loader ( &tracks );
        MIDIFileRead reader ( &rs, &track_loader );
        MIDISequencerGUIEventNotifierText gui ( stdout );
        MIDISequencer seq ( &tracks, &gui );
        MIDIDriverDump driver ( 128, stdout );
        MIDIManager mgr ( &driver, &gui );
        reader.Parse();
        seq.GoToZero();
        mgr.SetSeq ( &seq );
        DumpTrackNames ( &seq );
        PlayDumpManager ( &mgr );
    }

    return 0;
}
