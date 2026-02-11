_dlna_audio_rule_match_stream(const struct lms_dlna_audio_rule *rule,
                              const struct lms_stream *audio_stream) {

    if (audio_stream) {
        if (rule->bitrate &&
            (audio_stream->audio.bitrate < rule->bitrate->min ||
             audio_stream->audio.bitrate > rule->bitrate->max)) {
            return false;
        }
        if (rule->rates &&
            !_uint_vector_has_value(rule->rates->rates,
                                    audio_stream->audio.sampling_rate))
            return false;

        if (rule->channels &&
            (audio_stream->audio.channels < rule->channels->min ||
             audio_stream->audio.channels > rule->channels->max))
            return false;
    }

    if (audio_stream && rule->codec &&
        strcmp(audio_stream->codec.str, rule->codec->str))
        return false;

    return true;
}
