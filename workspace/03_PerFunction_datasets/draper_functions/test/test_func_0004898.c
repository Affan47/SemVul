find_codec_or_die(const char *name, int type, int encoder)
{
    const char *codec_string = encoder ? "encoder" : "decoder";
    AVCodec *codec;

    if(!name)
        return CODEC_ID_NONE;
    codec = encoder ?
        avcodec_find_encoder_by_name(name) :
        avcodec_find_decoder_by_name(name);
    if(!codec) {
        fprintf(stderr, "Unknown %s '%s'\n", codec_string, name);
        av_exit(1);
    }
    if(codec->type != type) {
        fprintf(stderr, "Invalid %s type '%s'\n", codec_string, name);
        av_exit(1);
    }
    return codec->id;
}
