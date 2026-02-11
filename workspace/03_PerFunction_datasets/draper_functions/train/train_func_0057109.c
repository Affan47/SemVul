_video_codec_id_to_str(uint8_t id[4])
{
    unsigned int i;

    for (i = 0; _video_codecs[i].name != &_str_unknown; i++)
        if (memcmp(id, _video_codecs[i].id, 4) == 0)
            return _video_codecs[i].name;

    return _video_codecs[i].name;
}
