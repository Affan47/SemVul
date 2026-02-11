mov_write_uuidusmt_tag(ByteIOContext *pb, AVFormatContext *s)
{
    AVMetadataTag *title = av_metadata_get(s->metadata, "title", NULL, 0);
    int64_t pos, pos2;

    if (title) {
        pos = url_ftell(pb);
        put_be32(pb, 0);
        put_tag(pb, "uuid");
        put_tag(pb, "USMT");
        put_be32(pb, 0x21d24fce);
        put_be32(pb, 0xbb88695c);
        put_be32(pb, 0xfac9c740);

        pos2 = url_ftell(pb);
        put_be32(pb, 0);
        put_tag(pb, "MTDT");
        put_be16(pb, 4);


        put_be16(pb, 0x0C);
        put_be32(pb, 0x0B);
        put_be16(pb, language_code("und"));
        put_be16(pb, 0x0);
        put_be16(pb, 0x021C);

        mov_write_psp_udta_tag(pb, LIBAVCODEC_IDENT,      "eng", 0x04);
        mov_write_psp_udta_tag(pb, title->value,          "eng", 0x01);

        mov_write_psp_udta_tag(pb, "2006/04/01 11:11:11", "und", 0x03);

        updateSize(pb, pos2);
        return updateSize(pb, pos);
    }

    return 0;
}
