IGetTime(const time_t* secs) const {
    tm* time = (fMode == kGMT) ? gmtime(secs) : localtime(secs);
    time->tm_isdst = -1;
    return time;
}
