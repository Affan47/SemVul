SetNoteMelodic( int const voice, int const note )
{
    opl->write( 0xb0+voice, bxRegister[voice] & ~0x20 );

    if( note != kSilenceNote )
    {
        SetFreq( voice, note, true );
    }
}
