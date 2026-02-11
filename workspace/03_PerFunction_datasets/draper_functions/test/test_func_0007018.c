put_swf_tag(AVFormatContext *s, int tag)
{
    SWFContext *swf = s->priv_data;
    ByteIOContext *pb = s->pb;

    swf->tag_pos = url_ftell(pb);
    swf->tag = tag;

    if (tag & TAG_LONG) {
        put_le16(pb, 0);
        put_le32(pb, 0);
    } else {
        put_le16(pb, 0);
    }
}
