init(void)
{
  freeze();
  _hadFocus=MSFalse;
  _cycle=0;
  _cycleTimer=0;
  _cycleInterval=MSEntryFieldDefaultCycleInterval;
  _cycleColorMode=MSForeground;
  _editor=0;
  _editor=new FieldEditor(this);
  _autoMaskInput=MSFalse;
  selectInput(MSEntryFieldEventMask);

  _selectionStart=-1;
  _selectionEnd=-1;
  _firstCharacter=0;
  _insertCursor=-1;
  _supportPasting=MSTrue;
  _pasting=MSFalse;
}
