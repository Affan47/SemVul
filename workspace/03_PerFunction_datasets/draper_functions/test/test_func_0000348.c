netsnmp_string_time_to_secs(const char *time_string) {
    int secs = -1;
    if (!time_string || !time_string[0])
        return secs;

    secs = atoi(time_string);

    if (isdigit((unsigned char)time_string[strlen(time_string)-1]))
        return secs;

    switch (time_string[strlen(time_string)-1]) {
    case 's':
    case 'S':

        break;

    case 'm':
    case 'M':
        secs = secs * 60;
        break;

    case 'h':
    case 'H':
        secs = secs * 60 * 60;
        break;

    case 'd':
    case 'D':
        secs = secs * 60 * 60 * 24;
        break;

    case 'w':
    case 'W':
        secs = secs * 60 * 60 * 24 * 7;
        break;

    default:
        snmp_log(LOG_ERR, "time string %s contains an invalid suffix letter\n",
                 time_string);
        return -1;
    }

    DEBUGMSGTL(("string_time_to_secs", "Converted time string %s to %d\n",
                time_string, secs));
    return secs;
}
