editorActivate(void)
{
  if (editor()->mapped()==MSTrue)
   {
     if (validate(editor()->string(),selectedRow())==MSTrue)
      {
	unmapEditor();
      }
   }
  return (editor()->mapped()==MSTrue)?MSFalse:MSTrue;
}
