get_width(const char *str, Font * altFont) {
    int width = 0;
    for (const char *p=str; *p; ++p) {

        int len = utf8NextCharSize(p);
        if (len == 0) {

            continue;
        }

        if (len > 1 || advance[int(*p)] == 0) {
            if (altFont != NULL) {
                std::string utf8char(p, len);
                width += altFont->get_width(utf8char.c_str());
            }
            p += len - 1;
        } else {
            width += get_width(*p);
        }
    }
    return width;
}
