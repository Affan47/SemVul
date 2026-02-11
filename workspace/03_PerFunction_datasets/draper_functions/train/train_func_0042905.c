rotTextWidth(const char * const text, unsigned int size) const {

    if (text == 0)
        return 0;

    unsigned int width = 0;
    for (size_t i = 0; i<size; i++) {
        int ichar = text[i] - 32;

        if (ichar >= 0 && ichar < 95)
            width += m_rotfont->per_char[ichar].width;
    }

    return width;
}
