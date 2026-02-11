isFileChannel(int channel)
{
    return ((abs(channel) < MAX_CHANNEL) && (is_channel_open[channel]));
}
