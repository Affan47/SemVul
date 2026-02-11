setFromString(char const *strval) {
    if (strcasecmp(strval, "Titlebar")==0)
        m_value= Fluxbox::ATTACH_AREA_TITLEBAR;
    else
        m_value= Fluxbox::ATTACH_AREA_WINDOW;
}
