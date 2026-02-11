refresh(void)
{
  if (mapped()==MSTrue)
   {
     clear();
     blinkPhase(Normal);
     redraw();
   }
}
