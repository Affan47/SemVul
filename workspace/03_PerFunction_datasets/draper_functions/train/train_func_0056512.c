anqfits_get_header_const(const anqfits_t* qf, int ext) {
    assert(ext >= 0 && ext < qf->Nexts);
    if (!qf->exts[ext].header) {
        off_t start, size;
        char* str;
        start = anqfits_header_start(qf, ext);
        size  = anqfits_header_size (qf, ext);
        if ((start == -1) || (size == -1)) {
            ERROR("failed to get header start + size for file \"%s\" extension %i", qf->filename, ext);
            return NULL;
        }
        str = file_get_contents_offset(qf->filename, (int)start, (int)size);
        if (!str) {
            ERROR("failed to read \"%s\" extension %i: offset %i size %i\n", qf->filename, ext, (int)start, (int)size);
            return NULL;
        }
        qf->exts[ext].header = qfits_header_read_hdr_string
            ((unsigned char*)str, (int)size);
    }
    return qf->exts[ext].header;
}
