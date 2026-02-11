getXftFont(ustring name, bool antialias) {
    ref<YFont>font(new YXftFont(name, false, antialias));
    if (font == null || !font->valid()) {
        msg("failed to load font '%s', trying fallback", cstring(name).c_str());
        font.init(new YXftFont("DejaVu Sans,sans-serif:size=11", false, antialias));
        if (font == null || !font->valid())
            msg("Could not load fallback Xft font.");
    }
    return font;
}
