ADDON_SetSetting(const char *settingName, const void *settingValue)
{
  XVDR::MutexLock lock(&addonMutex);

  bool bChanged = false;
  cXBMCSettings& s = cXBMCSettings::GetInstance();
  bChanged = s.set(settingName, settingValue);

  if(!bChanged)
    return ADDON_STATUS_OK;

  if(strcmp(settingName, "host") == 0 || strcmp(settingName, "piconpath") == 0)
    return ADDON_STATUS_NEED_RESTART;

  s.checkValues();

  mClient->SetTimeout(s.ConnectTimeout() * 1000);
  mClient->SetCompressionLevel(s.Compression() * 3);
  mClient->SetAudioType(s.AudioType());

  if(!bChanged)
    return ADDON_STATUS_OK;

  mClient->EnableStatusInterface(s.HandleMessages());
  mClient->SetUpdateChannels(s.UpdateChannels());
  mClient->ChannelFilter(s.FTAChannels(), s.NativeLangOnly(), s.vcaids);

  return ADDON_STATUS_OK;
}
