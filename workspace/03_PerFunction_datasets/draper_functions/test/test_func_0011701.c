check(const boost::function<void (const LocaleEnv &env)> &result)
{
    if (getConnection()) {
        SE_LOG_DEBUG(NULL, "localed: get current Locale property");
        m_propertiesGet.start(std::string(LOCALED_INTERFACE),
                              std::string(LOCALED_LOCALE_PROPERTY),
                              boost::bind(&LocaledListener::processLocaleProperty, m_self, _1, _2, true, result));
    } else {
        processLocaleProperty(LocaleVariant(), "no D-Bus connection", true, result);
    }
}
