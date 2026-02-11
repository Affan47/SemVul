out_push_stream(out_stream_info *stream)
{


    if (G_recurse != 0 && G_cur_stream != stream)
        return FALSE;


    G_cur_stream = stream;


    ++G_recurse;


    return TRUE;
}
