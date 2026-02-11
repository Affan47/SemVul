render(const FbTk::Texture &tex, FbTk::Color &col, Pixmap &pm,
                        unsigned int w, unsigned int h, FbTk::Orientation orient) {

    Pixmap tmp = pm;
    if (!tex.usePixmap()) {
        pm = None;
        col = tex.color();
    } else {
        pm = m_imagectrl.renderImage(w, h, tex, orient);
    }

    if (tmp)
        m_imagectrl.removeImage(tmp);

}
