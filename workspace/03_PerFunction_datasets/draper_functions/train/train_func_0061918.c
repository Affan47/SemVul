cursorPositionForw(unsigned position_)
{
  if(masking() == MSTrue) position_= _inputMask.indexOf(inputMaskCharacter(),position_);
  moveCursor(position_);
}
