RollingFileAppender(const Properties& properties)
    : FileAppender(properties, STD_NAMESPACE ios::app), maxFileSize (), maxBackupIndex ()
{
    long tmpMaxFileSize = DEFAULT_ROLLING_LOG_SIZE;
    int tmpMaxBackupIndex = 1;
    tstring tmp (
        helpers::toUpper (
            properties.getProperty (DCMTK_LOG4CPLUS_TEXT ("MaxFileSize"))));
    if (! tmp.empty ())
    {
        tmpMaxFileSize = atoi(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(tmp).c_str());
        if (tmpMaxFileSize != 0)
        {
            tstring::size_type const len = tmp.length();
            if (len > 2
                && tmp.compare (len - 2, 2, DCMTK_LOG4CPLUS_TEXT("MB")) == 0)
                tmpMaxFileSize *= (1024 * 1024);
            else if (len > 2
                && tmp.compare (len - 2, 2, DCMTK_LOG4CPLUS_TEXT("KB")) == 0)
                tmpMaxFileSize *= 1024;
        }
        tmpMaxFileSize = MAX(tmpMaxFileSize, MINIMUM_ROLLING_LOG_SIZE);
    }

    properties.getInt (tmpMaxBackupIndex, DCMTK_LOG4CPLUS_TEXT("MaxBackupIndex"));

    init(tmpMaxFileSize, tmpMaxBackupIndex);
}
