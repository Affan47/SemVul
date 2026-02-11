drawText(const FbDrawable &w, int screen, GC gc, const char* text, size_t len, int x, int y, FbTk::Orientation orient) {

    if (!text || !*text || m_fontstruct == 0)
        return;

    std::string localestr = FbStringUtil::FbStrToLocale(FbString(text, len));


    if (orient != ROT0 && validOrientation(orient)) {
        drawRotText(w.drawable(), screen, gc, localestr.c_str(), localestr.size(), x, y, orient);
        return;
    }

    XSetFont(w.display(), gc, m_fontstruct->fid);
    XDrawString(w.display(), w.drawable(), gc, x, y, localestr.data(), localestr.size());
}
