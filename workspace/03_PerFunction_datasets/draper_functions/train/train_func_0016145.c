initial_skeleton_page (format_plugin_t *plugin, ogg_page *page)
{
    ogg_state_t *ogg_info = plugin->_state;
    ogg_codec_t *codec = calloc (1, sizeof (ogg_codec_t));
    ogg_packet packet;

    ogg_stream_init (&codec->os, ogg_page_serialno (page));
    ogg_stream_pagein (&codec->os, page);

    ogg_stream_packetout (&codec->os, &packet);

    DEBUG0("checking for skeleton codec");

    if ((packet.bytes<8) || memcmp(packet.packet, "fishead\0", 8))
    {
        ogg_stream_clear (&codec->os);
        free (codec);
        return NULL;
    }

    INFO0 ("seen initial skeleton header");
    codec->process_page = process_skeleton_page;
    codec->codec_free = skeleton_codec_free;
    codec->headers = 1;
    codec->name = "Skeleton";

    format_ogg_attach_header (ogg_info, page);
    return codec;
}
