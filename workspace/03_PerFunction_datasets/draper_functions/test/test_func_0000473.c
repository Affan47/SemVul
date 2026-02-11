init(int row_count)
{
    rec_no    = 0;
    rec_pos   = 0;
    indic_len = 50;
    num_rec   = row_count;

    if (!m_showOutput)
        return;

    #ifdef _WIN32
    printf( "\x3D" );
    #else
    printf( "[" );
    #endif
    for ( int i = 0; i < indic_len; i++ ) printf( empty );
    #ifdef _WIN32
    printf( "\x3D 0%%\r\x3D" );
    #else
    printf( "] 0%%\r[" );
    #endif
    fflush(stdout);
}
