getCurrentTime()
{
    time_t seconds = time (NULL);
    tm tmbuffer;
    tm *data = localtime_r(&seconds, &tmbuffer);
    if (!data) {
        return "???";
    }
    arrayptr<char> buffer (new char [13]);
    strftime (buffer.get(), 13, "%y%m%d%H%M%S", data);
    return buffer.get();
}
