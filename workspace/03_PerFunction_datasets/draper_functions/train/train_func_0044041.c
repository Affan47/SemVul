ascent() const {
    if (m_fontstruct == 0)
        return 0;
    if (m_rotfont != 0)
        return m_rotfont->max_ascent;

    return m_fontstruct->ascent;
}
