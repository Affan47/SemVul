ebml_level_end(MatroskaDemuxContext *matroska)
{
    ByteIOContext *pb = matroska->ctx->pb;
    int64_t pos = url_ftell(pb);

    if (matroska->num_levels > 0) {
        MatroskaLevel *level = &matroska->levels[matroska->num_levels - 1];
        if (pos - level->start >= level->length) {
            matroska->num_levels--;
            return 1;
        }
    }
    return 0;
}
