do_font(ostream& out, const Font* font) {
    out << (double)font->size() << " /";
    const char* p = font->name();
    while (*p != '\0') {
        out << char(*p == ' ' ? '-' : *p);
        ++p;
    }
    out << " sf\n";
}
