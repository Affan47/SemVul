psyMainInit(PSY_KERNEL *hPsy,
                   Word32 sampleRate,
                   Word32 bitRate,
                   Word16 channels,
                   Word16 tnsMask,
                   Word16 bandwidth)
{
  Word16 ch, err;
  Word32 channelBitRate = bitRate/channels;

  err = InitPsyConfigurationLong(channelBitRate,
                                 sampleRate,
                                 bandwidth,
                                 &(hPsy->psyConfLong));

  if (!err) {
      hPsy->sampleRateIdx = hPsy->psyConfLong.sampRateIdx;
	  err = InitTnsConfigurationLong(bitRate, sampleRate, channels,
                                   &hPsy->psyConfLong.tnsConf, &hPsy->psyConfLong, tnsMask&2);
  }

  if (!err)
    err = InitPsyConfigurationShort(channelBitRate,
                                    sampleRate,
                                    bandwidth,
                                    &hPsy->psyConfShort);
  if (!err) {
    err = InitTnsConfigurationShort(bitRate, sampleRate, channels,
                                    &hPsy->psyConfShort.tnsConf, &hPsy->psyConfShort, tnsMask&1);
  }

  if (!err)
    for(ch=0;ch < channels;ch++){

      InitBlockSwitching(&hPsy->psyData[ch].blockSwitchingControl,
                         bitRate, channels);

      InitPreEchoControl(hPsy->psyData[ch].sfbThresholdnm1,
                         hPsy->psyConfLong.sfbCnt,
                         hPsy->psyConfLong.sfbThresholdQuiet);
      hPsy->psyData[ch].mdctScalenm1 = 0;
    }

	return(err);
}
