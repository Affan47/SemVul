GetTimeSigDenominator() const
{
    if ( !file_loaded )
    {
        return 4;
    }

    return seq.GetTrackState ( 0 )->timesig_denominator;
}
