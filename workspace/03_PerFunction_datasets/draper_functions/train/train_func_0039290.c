initElement(ELEMENT_INFO* elInfo, ELEMENT_TYPE elType)
{
  Word16 error=0;

  elInfo->elType=elType;

  switch(elInfo->elType) {

    case ID_SCE:
      elInfo->nChannelsInEl=1;

      elInfo->ChannelIndex[0]=0;

      elInfo->instanceTag=0;
      break;

    case ID_CPE:

      elInfo->nChannelsInEl=2;

      elInfo->ChannelIndex[0]=0;
      elInfo->ChannelIndex[1]=1;

      elInfo->instanceTag=0;
      break;

    default:
      error=1;
  }

  return error;
}
