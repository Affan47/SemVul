volumeChanged( int percent )
{
    DEBUG_BLOCK
    signalPropertyChange( "Volume", static_cast<double>(percent) / 100.0 );
}
