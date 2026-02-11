edit(void)
{
  if (editor()->mapped()==MSFalse)
   {
     editor()->editMode(MSTextField::InsertMode);
     moveEditorToSelection(selection());
   }
}
