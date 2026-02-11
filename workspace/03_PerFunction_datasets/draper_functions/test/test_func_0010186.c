MDFDefaultSaveRes(size_t ichannel) const
  {
    const float resAMTI[8] = { 0.01f, 0.01f, 0.06f, 0.03f, 0.03f, 0.01f, 0.1f, 0.1f };
    const float resKistler[8] = { 0.02f, 0.02f, 0.02f, 0.02f, 0.06f, 0.06f, 0.06f, 0.06f };

    if (ichannel > 7)
      return 1.0;

    if (HasAMTIChannelScheme())
      return resAMTI[ichannel];
    else
      return resKistler[ichannel];
  }
