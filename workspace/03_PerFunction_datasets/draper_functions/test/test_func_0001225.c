_audio_codec_id_to_str(uint16_t id)
{
    unsigned int i;

    for (i = 0; _audio_codecs[i].name != &_str_unknown; i++)
        if (_audio_codecs[i].id == id)
            return _audio_codecs[i].name;

    return _audio_codecs[i].name;
}
