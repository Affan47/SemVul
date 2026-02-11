get_logical_name(RESULT& result, string& path, string& name) {
    char buf[1024], phys_name[1024];
    MIOFILE mf;
    int retval;

    mf.init_buf_read(result.xml_doc_in);
    XML_PARSER xp(&mf);

    safe_strcpy(buf, path.c_str());
    char* p = strrchr(buf, '/');
    if (!p) return ERR_NOT_FOUND;
    safe_strcpy(phys_name, p+1);

    while (!xp.get_tag()) {
        if (!xp.is_tag) continue;
        if (xp.match_tag("result")) continue;
        if (xp.match_tag("file_ref")) {
            FILE_REF fr;
            retval = fr.parse(xp);
            if (retval) continue;
            if (!strcmp(phys_name, fr.file_name)) {
                name = fr.open_name;
                return 0;
            }
            continue;
        }
        xp.skip_unexpected(false, 0);
    }
    return ERR_XML_PARSE;
}
