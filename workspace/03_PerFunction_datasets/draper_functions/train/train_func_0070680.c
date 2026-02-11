Stop()
{
    if ( !file_loaded )
    {
        return;
    }

    if ( !mgr.IsSeqStop() )
    {
        mgr.SeqStop();
        driver.AllNotesOff();

        for ( int i = 0; i < seq.GetNumTracks(); ++i )
        {
            seq.GetTrackState ( i )->note_matrix.Clear();
        }
    }
}
