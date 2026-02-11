InitialiseEncoder (const dirac_encoder_context_t *enc_ctx, bool verbose, dirac_encoder_t *encoder)
{
    TEST (enc_ctx != NULL);
    TEST (encoder != NULL);

    if (enc_ctx->src_params.width == 0 || enc_ctx->src_params.height == 0)
        return false;

    if (enc_ctx->src_params.chroma < format444 ||
            enc_ctx->src_params.chroma >= formatNK)
        return false;

    if (!enc_ctx->src_params.frame_rate.numerator ||
            !enc_ctx->src_params.frame_rate.denominator)
        return false;

    memmove (&encoder->enc_ctx, enc_ctx, sizeof(dirac_encoder_context_t));

    encoder->dec_buf.id = 0;

    switch ( enc_ctx->src_params.chroma )
    {
    case format420:
         encoder->enc_ctx.src_params.chroma_width = enc_ctx->src_params.width/2;
         encoder->enc_ctx.src_params.chroma_height = enc_ctx->src_params.height/2;
         break;
    case format422:
         encoder->enc_ctx.src_params.chroma_width = enc_ctx->src_params.width/2;
         encoder->enc_ctx.src_params.chroma_height = enc_ctx->src_params.height;
         break;
    case format444:
    default:
         encoder->enc_ctx.src_params.chroma_width = enc_ctx->src_params.width;
         encoder->enc_ctx.src_params.chroma_height = enc_ctx->src_params.height;
         break;
    }

    try
    {
        DiracEncoder *comp = new DiracEncoder (&encoder->enc_ctx, verbose);

        encoder->compressor = comp;
        if (encoder->enc_ctx.decode_flag)
        {
            int bufsize = (encoder->enc_ctx.src_params.width * encoder->enc_ctx.src_params.height)+ 2*(encoder->enc_ctx.src_params.chroma_width*encoder->enc_ctx.src_params.chroma_height);
            encoder->dec_buf.buf[0] = new unsigned char [bufsize];
            encoder->dec_buf.buf[1] = encoder->dec_buf.buf[0] +
                (encoder->enc_ctx.src_params.width * encoder->enc_ctx.src_params.height);
            encoder->dec_buf.buf[2] = encoder->dec_buf.buf[1] +
                (encoder->enc_ctx.src_params.chroma_width*encoder->enc_ctx.src_params.chroma_height);

            comp->SetDecodeBuffer (encoder->dec_buf.buf[0], bufsize);
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}
