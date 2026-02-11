RollingFileAppender(const Properties& properties, tstring& error)
    : FileAppender(properties, error, STD_NAMESPACE ios::app)
{
    int maxFileSize_ = 10*1024*1024;
    int maxBackupIndex_ = 1;
    if(properties.exists( LOG4CPLUS_TEXT("MaxFileSize") )) {
        tstring tmp = properties.getProperty( LOG4CPLUS_TEXT("MaxFileSize") );
        tmp = helpers::toUpper(tmp);
        maxFileSize_ = atoi(LOG4CPLUS_TSTRING_TO_STRING(tmp).c_str());
        if(tmp.find( LOG4CPLUS_TEXT("MB") ) == (tmp.length() - 2)) {
            maxFileSize_ *= (1024 * 1024);
        }
        if(tmp.find( LOG4CPLUS_TEXT("KB") ) == (tmp.length() - 2)) {
            maxFileSize_ *= 1024;
        }
    }

    if(properties.exists( LOG4CPLUS_TEXT("MaxBackupIndex") )) {
        tstring tmp = properties.getProperty(LOG4CPLUS_TEXT("MaxBackupIndex"));
        maxBackupIndex_ = atoi(LOG4CPLUS_TSTRING_TO_STRING(tmp).c_str());
    }

    init(maxFileSize_, maxBackupIndex_);
}
