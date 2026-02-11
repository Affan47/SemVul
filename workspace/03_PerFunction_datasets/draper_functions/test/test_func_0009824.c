startEditing(MSTextField::EditingMode mode_,unsigned x_)
{

  if(masking() == MSTrue) mode_ = OverstrikeMode;
  if (editMode()!=mode_)
   {
     clearCursor();
     _editMode=mode_;
   }
  cursorPositionForw(computeCursorPosition(x_));
}
