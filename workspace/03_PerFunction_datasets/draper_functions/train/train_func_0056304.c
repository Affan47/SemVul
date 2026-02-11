x264_param_default_preset( x264_param_t *param, const char *preset, const char *tune )
{
    x264_param_default( param );

    if( preset && x264_param_apply_preset( param, preset ) < 0 )
        return -1;
    if( tune && x264_param_apply_tune( param, tune ) < 0 )
        return -1;
    return 0;
}
