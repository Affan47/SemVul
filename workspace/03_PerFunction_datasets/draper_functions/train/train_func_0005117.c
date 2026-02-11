aacEncDistributeSbrBits(CHANNEL_MAPPING *channelMapping, SBR_ELEMENT_INFO *sbrElInfo, INT bitRate)
{
  INT codebits = bitRate;
  int el;


  for (el=0; el<channelMapping->nElements; el++) {
      sbrElInfo[el].ChannelIndex[0] = channelMapping->elInfo[el].ChannelIndex[0];
      sbrElInfo[el].ChannelIndex[1] = channelMapping->elInfo[el].ChannelIndex[1];
      sbrElInfo[el].elType          = channelMapping->elInfo[el].elType;
      sbrElInfo[el].bitRate         = (INT)(fMultNorm(channelMapping->elInfo[el].relativeBits, (FIXP_DBL)bitRate));
      sbrElInfo[el].instanceTag     = channelMapping->elInfo[el].instanceTag;
      sbrElInfo[el].nChannelsInEl   = channelMapping->elInfo[el].nChannelsInEl;

      codebits -= sbrElInfo[el].bitRate;
  }
  sbrElInfo[0].bitRate += codebits;
}
