id3tag_set_albumart(lame_t gfp, const char *image, size_t size)
{
    int     mimetype = 0;
    unsigned char const *data = (unsigned char const *) image;
    lame_internal_flags *gfc = gfp->internal_flags;


    if (2 < size && data[0] == 0xFF && data[1] == 0xD8) {
        mimetype = MIMETYPE_JPEG;
    }
    else if (4 < size && data[0] == 0x89 && strncmp((const char *) &data[1], "PNG", 3) == 0) {
        mimetype = MIMETYPE_PNG;
    }
    else if (4 < size && strncmp((const char *) data, "GIF8", 4) == 0) {
        mimetype = MIMETYPE_GIF;
    }
    else {
        return -1;
    }
    if (gfc->tag_spec.albumart != 0) {
        free(gfc->tag_spec.albumart);
        gfc->tag_spec.albumart = 0;
        gfc->tag_spec.albumart_size = 0;
        gfc->tag_spec.albumart_mimetype = MIMETYPE_NONE;
    }
    if (size < 1) {
        return 0;
    }
    gfc->tag_spec.albumart = lame_calloc(unsigned char, size);
    if (gfc->tag_spec.albumart != 0) {
        memcpy(gfc->tag_spec.albumart, image, size);
        gfc->tag_spec.albumart_size = (unsigned int)size;
        gfc->tag_spec.albumart_mimetype = mimetype;
        gfc->tag_spec.flags |= CHANGED_FLAG;
        id3tag_add_v2(gfp);
    }
    return 0;
}
