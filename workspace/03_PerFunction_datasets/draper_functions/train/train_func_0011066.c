print( const RtAudioDeviceInfo & info )
{
    EM_error2b( 0, "device name = \"%s\"", info.name.c_str() );
    if (info.probed == false)
        EM_error2b( 0, "probe [failed] ..." );
    else
    {
        EM_error2b( 0, "probe [success] ..." );
        EM_error2b( 0, "# output channels = %d", info.outputChannels );
        EM_error2b( 0, "# input channels  = %d", info.inputChannels );
        EM_error2b( 0, "# duplex Channels = %d", info.duplexChannels );
        if( info.isDefault ) EM_error2b( 0, "default device = YES" );
        else EM_error2b( 0, "default device = NO" );
        if( info.nativeFormats == 0 ) EM_error2b( 0, "no natively supported data formats(?)!" );
        else
        {
            EM_error2b( 0,  "natively supported data formats:" );
            if( info.nativeFormats & RTAUDIO_SINT8 )   EM_error2b( 0, "   8-bit int" );
            if( info.nativeFormats & RTAUDIO_SINT16 )  EM_error2b( 0, "  16-bit int" );
            if( info.nativeFormats & RTAUDIO_SINT24 )  EM_error2b( 0, "  24-bit int" );
            if( info.nativeFormats & RTAUDIO_SINT32 )  EM_error2b( 0, "  32-bit int" );
            if( info.nativeFormats & RTAUDIO_FLOAT32 ) EM_error2b( 0, "  32-bit float" );
            if( info.nativeFormats & RTAUDIO_FLOAT64 ) EM_error2b( 0, "  64-bit float" );
        }
        if ( info.sampleRates.size() < 1 ) EM_error2b( 0,"no supported sample rates found!" );
        else
        {
            EM_error2b( 0, "supported sample rates:" );
            for( unsigned int j = 0; j < info.sampleRates.size(); j++ )
                EM_error2b( 0, "  %d Hz", info.sampleRates[j] );
        }
    }
}
