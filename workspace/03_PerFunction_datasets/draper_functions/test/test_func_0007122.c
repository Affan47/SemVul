delete_old_log(timeval tv) {
    if (_retain_day <= 0) {
        return 0;
    }
    struct timeval old_tv;
    old_tv.tv_sec = tv.tv_sec - _retain_day * 3600 * 24;
    old_tv.tv_usec = tv.tv_usec;
    char old_file[100];
    memset(old_file, 0, 100);
    struct tm *tm;
    tm = localtime(&old_tv.tv_sec);
    sprintf(old_file, "%s.%04d-%02d-%02d",
            _log_file.c_str(), tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday - 1);
    std::string old_file_path = _log_dir + "/" + old_file;
    return remove(old_file_path.c_str());
}
