open_file( char *psz_filename, hnd_t *p_handle, video_info_t *info, cli_input_opt_t *opt )
{
    int ret = 0;
    FILE *tcfile_in;
    timecode_hnd_t *h = malloc( sizeof(timecode_hnd_t) );
    FAIL_IF_ERROR( !h, "malloc failed\n" )
    h->input = cli_input;
    h->p_handle = *p_handle;
    h->pts = NULL;
    if( opt->timebase )
    {
        ret = sscanf( opt->timebase, "%"SCNu64"/%"SCNu64, &h->timebase_num, &h->timebase_den );
        if( ret == 1 )
        {
            h->timebase_num = strtoul( opt->timebase, NULL, 10 );
            h->timebase_den = 0;
        }
        FAIL_IF_ERROR( h->timebase_num > UINT32_MAX || h->timebase_den > UINT32_MAX,
                       "timebase you specified exceeds H.264 maximum\n" )
    }
    h->auto_timebase_num = !ret;
    h->auto_timebase_den = ret < 2;
    if( h->auto_timebase_num )
        h->timebase_num = info->fps_den;
    if( h->auto_timebase_den )
        h->timebase_den = 0;
    timecode_input.picture_alloc = h->input.picture_alloc;
    timecode_input.picture_clean = h->input.picture_clean;

    tcfile_in = fopen( psz_filename, "rb" );
    FAIL_IF_ERROR( !tcfile_in, "can't open `%s'\n", psz_filename )
    else if( !x264_is_regular_file( tcfile_in ) )
    {
        x264_cli_log( "timecode", X264_LOG_ERROR, "tcfile input incompatible with non-regular file `%s'\n", psz_filename );
        fclose( tcfile_in );
        return -1;
    }

    if( parse_tcfile( tcfile_in, h, info ) < 0 )
    {
        if( h->pts )
            free( h->pts );
        fclose( tcfile_in );
        return -1;
    }
    fclose( tcfile_in );

    info->timebase_num = h->timebase_num;
    info->timebase_den = h->timebase_den;
    info->vfr = 1;

    *p_handle = h;
    return 0;
}
