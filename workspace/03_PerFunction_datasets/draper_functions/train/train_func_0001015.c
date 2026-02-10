FDKaacEnc_getChannelAssignment(CHANNEL_MODE encMode, CHANNEL_ORDER co)
{
  const CHANNEL_ASSIGNMENT_INFO_TAB *pTab;
  int i;

  if (co == CH_ORDER_MPEG)
    pTab = assignmentInfoTabMpeg;
  else if (co == CH_ORDER_WAV)
    pTab = assignmentInfoTabWav;
  else
    pTab = assignmentInfoTabWg4;

  for(i=MAX_MODES-1; i>0; i--) {
    if (encMode== pTab[i].encoderMode) {
      break;
    }
  }
  return (pTab[i].channel_assignment);
}
