dirac_decoder_init(int verbose)
{
    dirac_decoder_t* decoder = new dirac_decoder_t;
    memset (decoder, 0, sizeof(dirac_decoder_t));

    bool verbosity = verbose > 0 ? true : false;
    DiracParser *parser = new DiracParser(verbosity);
    decoder->parser = static_cast<void *>(parser);

    decoder->fbuf = new dirac_framebuf_t;
    decoder->fbuf->id = NULL;
    decoder->fbuf->buf[0] = decoder->fbuf->buf[1] = decoder->fbuf->buf[2] = NULL;
    return decoder;
}
