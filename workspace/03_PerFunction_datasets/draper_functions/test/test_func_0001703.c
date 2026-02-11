init(void)
{
  _titleAlignment=MSCenter|MSBottom;
  create();

  if (owner()==0)
   {
     _titleFg=server()->defaultForeground();
     _titleFont=server()->defaultFont();
   }
  else
   {
     _titleFg=owner()->foreground();
     _titleFont=owner()->font();
   }
}
