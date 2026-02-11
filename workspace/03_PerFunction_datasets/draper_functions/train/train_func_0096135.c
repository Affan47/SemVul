PopupTipWindow(int px, int py, const char *text)
{
  int newx, newy;
  Window child;

  Tip.px = px;
  Tip.py = py;
  if (!ShowTips)
    return;
  if (Tip.win != None)
    DestroyTipWindow();

  Tip.tw = FlocaleTextWidth(FStatusFont, (char *)text, strlen(text)) + 6;
  Tip.th = FStatusFont->height + 4;
  XTranslateCoordinates(dpy, win, Root, px, py, &newx, &newy, &child);

  Tip.x = newx;

  if (win_y < Midline)
    Tip.y = newy + RowHeight;
  else
    Tip.y = newy - Tip.th -2;

  Tip.w = Tip.tw;
  Tip.h = Tip.th;

  if (Tip.x + Tip.tw + 4 > screen_g.x + screen_g.width - 5)
    Tip.x = screen_g.x + screen_g.width - Tip.tw - 9;
  if (Tip.x < screen_g.x + 5)
    Tip.x = screen_g.x + 5;

  UpdateString(&Tip.text, text);
  CreateTipWindow(Tip.x, Tip.y, Tip.w, Tip.h);

  if (Tip.open)
    XMapRaised(dpy, Tip.win);
}
