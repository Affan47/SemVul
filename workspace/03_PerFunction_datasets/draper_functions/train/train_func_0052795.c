load(const string *o_name, const string *o_altname) {
    const string &m_name = (o_name==0)?name():*o_name;
    const string &m_altname = (o_altname==0)?altName():*o_altname;

    string color_name(ThemeManager::instance().
                      resourceValue(m_name+".color", m_altname+".Color"));
    string colorto_name(ThemeManager::instance().
                        resourceValue(m_name+".colorTo", m_altname+".ColorTo"));
    string pixmap_name(ThemeManager::instance().
                       resourceValue(m_name+".pixmap", m_altname+".Pixmap"));


    if (!m_value.color().setFromString(color_name.c_str(),
                                       m_tm.screenNum()))
        m_value.color().setFromString("darkgray", m_tm.screenNum());

    if (!m_value.colorTo().setFromString(colorto_name.c_str(),
                                         m_tm.screenNum()))
        m_value.colorTo().setFromString("white", m_tm.screenNum());


    if ((m_value.type() & Texture::SOLID) != 0 && (m_value.type() & Texture::FLAT) == 0)
        m_value.calcHiLoColors(m_tm.screenNum());

    StringUtil::removeFirstWhitespace(pixmap_name);
    StringUtil::removeTrailingWhitespace(pixmap_name);
    if (pixmap_name.empty()) {
        m_value.pixmap() = 0;
        return;
    }

    std::auto_ptr<PixmapWithMask> pm(Image::load(pixmap_name, m_tm.screenNum()));

    if (pm.get() == 0) {
        if (ThemeManager::instance().verbose()) {
            cerr<<"Resource("<<m_name+".pixmap"
                <<"): Failed to load image: "<<pixmap_name<<endl;
        }
        m_value.pixmap() = 0;
    } else
        m_value.pixmap() = pm->pixmap().release();

}
