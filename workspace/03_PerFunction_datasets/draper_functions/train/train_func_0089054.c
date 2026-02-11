init(bool bColors)
{
  if (bColors)
    NCursesWindow::useColors();

  if (Root_Window->colors() > 1) {
    b_Colors = TRUE;
    Root_Window->setcolor(1);
    Root_Window->setpalette(COLOR_YELLOW,COLOR_BLUE);
    Root_Window->setcolor(2);
    Root_Window->setpalette(COLOR_CYAN,COLOR_BLUE);
    Root_Window->setcolor(3);
    Root_Window->setpalette(COLOR_BLACK,COLOR_BLUE);
    Root_Window->setcolor(4);
    Root_Window->setpalette(COLOR_BLACK,COLOR_CYAN);
    Root_Window->setcolor(5);
    Root_Window->setpalette(COLOR_BLUE,COLOR_YELLOW);
    Root_Window->setcolor(6);
    Root_Window->setpalette(COLOR_BLACK,COLOR_GREEN);
  }
  else
    b_Colors = FALSE;

  Root_Window->bkgd(' '|window_backgrounds());
}
