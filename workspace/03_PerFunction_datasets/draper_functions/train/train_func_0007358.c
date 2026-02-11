OpenLiveStream(const PVR_CHANNEL &channel)
{
  mClient->Lock();

  if (mDemuxer)
  {
    mDemuxer->Close();
    delete mDemuxer;
  }

  cXBMCSettings& s = cXBMCSettings::GetInstance();
  PacketBuffer* buf = NULL;


  if(s.TSMethod() == 0) {
    XBMC->Log(LOG_NOTICE, "doing simple server-side timeshift");
  }


  else if(s.TSMethod() == 1) {
    buf = (s.TSBufferSize() > 0) ? PacketBuffer::create(s.TSBufferSize() * 1024 * 1024) : NULL;
    if(buf != NULL) {
      XBMC->Log(LOG_NOTICE, "doing timeshift in memory using %f Mb RAM", s.TSBufferSize());
    }
  }


  else if(s.TSMethod() == 2) {
    std::string tsfile = s.TSFolder();


    if(tsfile.empty()) {
      XVDR::ClientInterface::GetTempFolder(tsfile);
    }

    XVDR::ClientInterface::TrimPath(tsfile, true);
    tsfile += "xvdr-timeshift.dat";

    buf = (s.TSBufferSizeHDD() > 0) ? PacketBuffer::create(s.TSBufferSizeHDD() * 1024 * 1024, tsfile) : NULL;
    if(buf != NULL) {
      XBMC->Log(LOG_NOTICE, "doing timeshift on hdd at '%s' using %f Mb", tsfile.c_str(), s.TSBufferSizeHDD());
    }
  }

  mDemuxer = new Demux(mClient, buf);
  mDemuxer->SetTimeout(cXBMCSettings::GetInstance().ConnectTimeout() * 1000);
  mDemuxer->SetAudioType(cXBMCSettings::GetInstance().AudioType());
  mDemuxer->SetPriority(priotable[cXBMCSettings::GetInstance().Priority()]);

  if(!channel.bIsRadio) {
    mDemuxer->SetStartWithIFrame(cXBMCSettings::GetInstance().StartWithIFrame());
  }

  const cXBMCSettings& settings = cXBMCSettings::GetInstance();
  Demux::SwitchStatus status = mDemuxer->OpenChannel(settings.Hostname(), channel.iUniqueId, settings.ClientName());

  if (status == Demux::SC_OK)
    CurrentChannel = channel.iChannelNumber;
  else
    ChannelNotification(status);

  mClient->Unlock();

  return (status == Demux::SC_OK);
}
