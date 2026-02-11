slotDigitizeScale(bool toggle)
{
  if (toggle)
  {
    slotStatusNormalMsg(QString(tr("Digitize scale bar...")));

    setDigitizeState(ScaleState);
  }
}
