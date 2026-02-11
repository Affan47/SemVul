redraw(void)
{
  if (mapped()==MSTrue)
   {
     drawBackground();
     drawShadow();
     drawText();
     if (haveFocus()==MSTrue&&cursorOn()==MSTrue)
      { (editMode()==InsertMode)?drawInsertCursor():drawOverstrikeCursor(); }
   }
}
