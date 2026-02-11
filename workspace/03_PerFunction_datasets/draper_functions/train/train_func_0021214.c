parse_buffer_embed(char* buf) {
    MIOFILE mf;
    char tag[4096];
    bool is_tag;
    int s_found = false;

    mf.init_buf_read(buf);
    XML_PARSER xp(&mf);
    while (!xp.get(tag, sizeof(tag), is_tag)) {
        if (xp.match_tag("signatures")) {
            s_found = true;
            break;
        }
    }
    if (s_found)
        return this->parse(xp);
    else
        return false;
}
