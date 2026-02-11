avi_write_info_tag2(AVFormatContext *s, const char *fourcc, const char *key1, const char *key2)
{
    AVMetadataTag *tag= av_metadata_get(s->metadata, key1, NULL, 0);
    if(!tag && key2)
        tag= av_metadata_get(s->metadata, key2, NULL, 0);
    if(tag)
        avi_write_info_tag(s->pb, fourcc, tag->value);
}
