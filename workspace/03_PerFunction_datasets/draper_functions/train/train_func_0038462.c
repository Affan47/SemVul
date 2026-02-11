get_time_string()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[1024];
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 1024, "%Y-%m-%d-%H%M%S", timeinfo);
    return buffer;
}
