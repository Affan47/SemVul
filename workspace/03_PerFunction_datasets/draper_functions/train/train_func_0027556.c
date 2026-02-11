editorEscape(void)
{
  if (editor()->mapped()==MSTrue)
   {
     focusOutNotify(editor());
     editor()->unmap();
   }
}
