init(long maxFileSize_, int maxBackupIndex_)
{
    if (maxFileSize_ < MINIMUM_ROLLING_LOG_SIZE)
    {
        tostringstream oss;
        oss << LOG4CPLUS_TEXT ("RollingFileAppender: MaxFileSize property")
            LOG4CPLUS_TEXT (" value is too small. Resetting to ")
            << MINIMUM_ROLLING_LOG_SIZE << ".";
        getLogLog ().warn (oss.str ());
        maxFileSize_ = MINIMUM_ROLLING_LOG_SIZE;
    }

    this->maxFileSize = maxFileSize_;
    this->maxBackupIndex = (std::max)(maxBackupIndex_, 1);
}
