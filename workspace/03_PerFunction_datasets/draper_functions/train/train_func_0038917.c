adcRead (uint8_t channelNum)
{
  adcMutex = 1;
  if (!_adcInitialised) adcInit();

  uint32_t regVal, adcData;


  if ( channelNum >= 8 )
  {

    channelNum = 0;
  }


  ADC_AD0CR &= ~ADC_AD0CR_SEL_MASK;


  ADC_AD0CR |= ADC_AD0CR_START_STARTNOW | (1 << channelNum);


  while ( 1 )
  {

    switch (channelNum)
    {
      case 0:
        regVal = (*(pREG32(ADC_AD0DR0)));
        break;
      case 1:
        regVal = (*(pREG32(ADC_AD0DR1)));
        break;
      case 2:
        regVal = (*(pREG32(ADC_AD0DR2)));
        break;
      case 3:
        regVal = (*(pREG32(ADC_AD0DR3)));
        break;
      case 4:
        regVal = (*(pREG32(ADC_AD0DR4)));
        break;
      case 5:
        regVal = (*(pREG32(ADC_AD0DR5)));
        break;
      case 6:
        regVal = (*(pREG32(ADC_AD0DR6)));
        break;
      case 7:
        regVal = (*(pREG32(ADC_AD0DR7)));
        break;
      default:
        regVal = (*(pREG32(ADC_AD0DR0)));
        break;
    }


    if (regVal & ADC_DR_DONE)
    {
      break;
    }
  }


  ADC_AD0CR &= ~ADC_AD0CR_START_MASK;


  if ( regVal & ADC_DR_OVERRUN )
  {
    adcMutex = 0;
    return (1);
  }


  adcData = (regVal >> 6) & 0x3FF;
  adcMutex = 0;
  return (adcData);
}
