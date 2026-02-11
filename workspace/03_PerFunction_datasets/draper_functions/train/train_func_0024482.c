oss_reset_playback(ALCdevice *device)
{
    oss_data *data = (oss_data*)device->ExtraData;
    int numFragmentsLogSize;
    int log2FragmentSize;
    unsigned int periods;
    audio_buf_info info;
    ALuint frameSize;
    int numChannels;
    int ossFormat;
    int ossSpeed;
    char *err;

    switch(device->FmtType)
    {
        case DevFmtByte:
            ossFormat = AFMT_S8;
            break;
        case DevFmtUByte:
            ossFormat = AFMT_U8;
            break;
        case DevFmtUShort:
        case DevFmtInt:
        case DevFmtUInt:
        case DevFmtFloat:
            device->FmtType = DevFmtShort;

        case DevFmtShort:
            ossFormat = AFMT_S16_NE;
            break;
    }

    periods = device->NumUpdates;
    numChannels = ChannelsFromDevFmt(device->FmtChans);
    frameSize = numChannels * BytesFromDevFmt(device->FmtType);

    ossSpeed = device->Frequency;
    log2FragmentSize = log2i(device->UpdateSize * frameSize);


    if (log2FragmentSize < 4)
        log2FragmentSize = 4;


    if(periods > 2) periods--;
    numFragmentsLogSize = (periods << 16) | log2FragmentSize;

#define CHECKERR(func) if((func) < 0) {                                       \
    err = #func;                                                              \
    goto err;                                                                 \
}


    ioctl(data->fd, SNDCTL_DSP_SETFRAGMENT, &numFragmentsLogSize);
    CHECKERR(ioctl(data->fd, SNDCTL_DSP_SETFMT, &ossFormat));
    CHECKERR(ioctl(data->fd, SNDCTL_DSP_CHANNELS, &numChannels));
    CHECKERR(ioctl(data->fd, SNDCTL_DSP_SPEED, &ossSpeed));
    CHECKERR(ioctl(data->fd, SNDCTL_DSP_GETOSPACE, &info));
    if(0)
    {
    err:
        ERR("%s failed: %s\n", err, strerror(errno));
        return ALC_FALSE;
    }
#undef CHECKERR

    if((int)ChannelsFromDevFmt(device->FmtChans) != numChannels)
    {
        ERR("Failed to set %s, got %d channels instead\n", DevFmtChannelsString(device->FmtChans), numChannels);
        return ALC_FALSE;
    }

    if(!((ossFormat == AFMT_S8 && device->FmtType == DevFmtByte) ||
         (ossFormat == AFMT_U8 && device->FmtType == DevFmtUByte) ||
         (ossFormat == AFMT_S16_NE && device->FmtType == DevFmtShort)))
    {
        ERR("Failed to set %s samples, got OSS format %#x\n", DevFmtTypeString(device->FmtType), ossFormat);
        return ALC_FALSE;
    }

    device->Frequency = ossSpeed;
    device->UpdateSize = info.fragsize / frameSize;
    device->NumUpdates = info.fragments + 1;

    SetDefaultChannelOrder(device);

    return ALC_TRUE;
}
