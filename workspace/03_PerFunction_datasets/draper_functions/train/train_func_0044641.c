Init()
{
    const char DSP_DEVICE[] = "/dev/dsp";
    const char DEVDSP_DEVICE[] = "/dev/sound/dsp";
    const char MIXER_DEVICE[] = "/dev/mixer";
    const char DEVMIXER_DEVICE[] = "/dev/sound/mixer";

#ifdef __linux__
#define NDELAY_FLAG O_NDELAY
#else
#define NDELAY_FLAG 0
#endif

    m_iMixFd = ::open(DEVMIXER_DEVICE, O_RDONLY);
    if (m_iMixFd < 0)
	m_iMixFd = ::open(MIXER_DEVICE, O_RDONLY);

    m_iAudioFd = ::open(DEVDSP_DEVICE, O_WRONLY | NDELAY_FLAG);
    if (m_iAudioFd < 0)
	m_iAudioFd = ::open(DSP_DEVICE, O_WRONLY | NDELAY_FLAG);
    for (;;)
    {
	if (m_iAudioFd < 0)
	{

	    AVM_WRITE("OSS audio renderer", "Can't open %s audio device: %s\n", DSP_DEVICE, strerror(errno));
	    break;
	}
#ifdef __linux__
	int flag = fcntl(m_iAudioFd, F_GETFL, 0);
	if (flag < 0)
	    break;
	flag &= ~O_NDELAY;
	if (fcntl(m_iAudioFd, F_SETFL, flag) < 0)
	    break;
#endif
	m_uiWriteSize = m_Owf.nBlockAlign;
	if (m_Owf.wFormatTag == 0x01)
	{
	    if (reset() != 0)
		return -1;
	    audio_buf_info zz;
	    ioctl(m_iAudioFd, SNDCTL_DSP_GETOSPACE, &zz);
	    m_iSndLimit = zz.bytes;
	    ioctl(m_iAudioFd, SNDCTL_DSP_GETBLKSIZE, &m_uiWriteSize);
	    AVM_WRITE("OSS audio renderer", "frags=%d  size=%db  buffer=%db (%db)\n",
		      zz.fragments, zz.fragsize, m_iSndLimit, m_uiWriteSize);
	}
	else if (m_Owf.wFormatTag == 0x2000)
	{
	    m_uiWriteSize = m_Owf.nBlockAlign;

	    int tmp = AFMT_AC3;
	    if (ioctl(m_iAudioFd, SNDCTL_DSP_SETFMT, &tmp) < 0 || tmp != AFMT_AC3)
	    {
		AVM_WRITE("OSS audio renderer", "AC3 SNDCTL_DSP_SETFMT failed"
			  "** Have you set emu10k1 into proper state?? (see README) **\n");
                break;
	    }
	    else
		AVM_WRITE("OSS audio renderer", "AC3 pass-through enabled\n");
	}

	m_AudioMix.m_iFd = m_iAudioFd;
        mixer(GET);

	m_pAudioThread = new PthreadTask(0, doAudioOut, (void*)this);
        return 0;
    }
    return -1;
}
