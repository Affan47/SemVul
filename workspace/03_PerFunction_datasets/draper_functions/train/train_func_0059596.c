open()
{
    const string &database = getDatabaseID();
    const string prefix("file://");
    string basedir;
    bool createDir = false;

    std::string varname = StringPrintf("SYNCEVOLUTION_FILE_SOURCE_DELAY_OPEN_%s", getDisplayName().c_str());
    const char *delay = getenv(varname.c_str());
    if (delay) {
        int seconds = atoi(delay);
        SE_LOG_DEBUG(getDisplayName(), "sleeping %ds while opening file source", seconds);
        Sleep(seconds);
        SE_LOG_DEBUG(getDisplayName(), "continue opening file source");
    }


    if (boost::starts_with(database, prefix)) {
        basedir = database.substr(prefix.size());
        createDir = true;
    } else {
        basedir = database;
    }


    if (!isDir(basedir)) {
        if (errno == ENOENT && createDir) {
            mkdir_p(basedir.c_str());
        } else {
            throwError(basedir, errno);
        }
    }


    m_basedir = basedir;
}
