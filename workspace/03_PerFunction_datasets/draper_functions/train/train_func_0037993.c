select_cursor ( tdmInteractor I, int id)
{
  DEFDATA(I,CursorData) ;

  ENTRY(("select_cursor(0x%x, %d)", I, id));

  if (PDATA(mode) == XmCURSOR_MODE)
    {
      PDATA(selected)[id] = TRUE;
    }
  else
    {
      PDATA(roam_selected) = TRUE;
    }

  EXIT((""));
  return OK;
}
