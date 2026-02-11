x264_strcat_filename( char *input, char *suffix )
{
    char *output = x264_malloc( strlen( input ) + strlen( suffix ) + 1 );
    if( !output )
        return NULL;
    strcpy( output, input );
    strcat( output, suffix );
    return output;
}
