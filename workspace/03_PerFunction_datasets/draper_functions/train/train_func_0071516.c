DrawRectangle (CONST int x1, CONST int y1, CONST int x2, CONST int y2, CONST int color)
{
#ifdef MITSHM
  if (shm)
    {
      Line (x1, y1, x2, y1, color);
      Line (x2, y1, x2, y2, color);
      Line (x2, y2, x1, y2, color);
      Line (x1, y2, x1, y1, color);
    }
  else
#endif
    {
      SetColor (color);
      XDrawRectangle (dp, current.pixmap, gc, (int) x1, (int) y1, (int) x2 - x1, (int) y2 - y1);
    }
}
