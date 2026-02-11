hpaioConnClose( hpaioScanner_t hpaio )
{
    if (hpaio->cmd_channelid > 0)
       hpmud_close_channel(hpaio->deviceid, hpaio->cmd_channelid);
    hpaio->cmd_channelid = -1;
    if (hpaio->scan_channelid > 0)
       hpmud_close_channel(hpaio->deviceid, hpaio->scan_channelid);
    hpaio->scan_channelid = -1;

    return 0;
}
