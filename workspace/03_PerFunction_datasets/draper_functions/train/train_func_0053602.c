popSaveElement()
{
  OpenElement *e = ContentState::popSaveElement();


  if (markedSectionSpecialLevel_ == 0) {
    currentMode_ = contentMode();
    specialParseInputLevel_ = 0;
  }
  pcdataRecovering_ = 0;
  return e;
}
