x264_cli_pic_size( int csp, int width, int height )
{
    if( x264_cli_csp_is_invalid( csp ) )
        return 0;
    uint64_t size = 0;
    int csp_mask = csp & X264_CSP_MASK;
    for( int i = 0; i < x264_cli_csps[csp_mask].planes; i++ )
        size += x264_cli_pic_plane_size( csp, width, height, i );
    return size;
}
