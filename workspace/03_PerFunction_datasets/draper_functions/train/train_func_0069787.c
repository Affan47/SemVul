LogSNCL(char *station, char *network, char *channel, char *location)
{
    if (parse_state == 0)
    {
        sprintf(looperrstr, "LogSNCL: ParseDiskLoopConfig not run yet");
        return looperrstr;
    }
    strcpy(station, log_station);
    strcpy(network, log_network);
    strcpy(channel, log_channel);
    strcpy(location, log_location);
    return NULL;
}
