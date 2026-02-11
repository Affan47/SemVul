drawText(const FbDrawable &w, int screen, GC gc,
                    const char *text, size_t len, int x, int y,
                    bool rotate) const {
    if (text == 0 || len == 0)
        return;

    char* rtext = 0;


    static bool first_run = true;

#ifdef HAVE_ICONV
    if (m_fontimp->utf8() && m_iconv != (iconv_t)(-1) && first_run) {
        rtext = recode(m_iconv, text, len);
        if (rtext != 0) {
            len = strlen(rtext);

        }
    }
#endif

    const char *real_text = rtext ? rtext : text;


    if (first_run) {
        if (m_shadow) {
            FbTk::GContext shadow_gc(w);
            shadow_gc.setForeground(m_shadow_color);
            first_run = false;
            drawText(w, screen, shadow_gc.gc(), real_text, len,
                     x + m_shadow_offx, y + m_shadow_offy, rotate);
            first_run = true;
        } else if (m_halo) {
            FbTk::GContext halo_gc(w);
            halo_gc.setForeground(m_halo_color);
            first_run = false;
            drawText(w, screen, halo_gc.gc(), real_text, len, x + 1, y + 1, rotate);
            drawText(w, screen, halo_gc.gc(), real_text, len, x - 1, y + 1, rotate);
            drawText(w, screen, halo_gc.gc(), real_text, len, x - 1, y - 1, rotate);
            drawText(w, screen, halo_gc.gc(), real_text, len, x + 1, y - 1, rotate);
            first_run = true;
        }
    }

    if (!rotate && isRotated()) {


        try {
            XFontImp *font = dynamic_cast<XFontImp *>(m_fontimp);
            font->setRotate(false);

            font->drawText(w, screen, gc, real_text, len, x, y);
            font->setRotate(true);
        } catch (std::bad_cast &bc) {

            m_fontimp->drawText(w, screen, gc, real_text, len, x, y);
        }

    } else
        m_fontimp->drawText(w, screen, gc, real_text, len, x, y);

    if (rtext != 0)
        delete[] rtext;

}
