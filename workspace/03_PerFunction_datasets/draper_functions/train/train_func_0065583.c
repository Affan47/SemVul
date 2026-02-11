get_buffer_finished (ogg_state_t *ogg_info, ogg_codec_t *codec)
{
    vorbis_codec_t *source_vorbis = codec->specific;
    ogg_page page;
    refbuf_t *refbuf;

    if (ogg_stream_flush (&source_vorbis->new_os, &page) > 0)
    {
        source_vorbis->samples_in_page -= (ogg_page_granulepos (&page) - source_vorbis->prev_page_samples);
        source_vorbis->prev_page_samples = ogg_page_granulepos (&page);

        refbuf = make_refbuf_with_page (&page);
        DEBUG0 ("flushing page");
        return refbuf;
    }
    ogg_stream_clear (&source_vorbis->new_os);
    ogg_stream_init (&source_vorbis->new_os, rand());

    format_ogg_free_headers (ogg_info);
    source_vorbis->get_buffer_page = NULL;
    if (source_vorbis->prev_packet)
        source_vorbis->process_packet = process_vorbis_headers;
    else
        source_vorbis->process_packet = NULL;

    if (source_vorbis->initial_audio_packet == 0)
        source_vorbis->prev_window = 0;

    return NULL;
}
