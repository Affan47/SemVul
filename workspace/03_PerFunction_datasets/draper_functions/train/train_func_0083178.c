butList_changeLine(But *but, int line, const char *text)  {
  List  *l = but->iPacket;

  assert(MAGIC(l));
  if (line >= l->numLines)  {
    butList_setLen(but, line + 1);
    butList_resize(but, but->x, but->y, but->w);
  }
  str_copyChars(&l->lines[line].str, text);
  if (str_len(&l->lines[line].str) == 0)  {
    l->lines[line].pressable = FALSE;
    if (l->selectLine == line)
      l->selectLine = -1;
    if (l->pressLine == line)
      l->pressLine = -1;
  } else  {
    l->lines[line].pressable = TRUE;
  }
  drawLine(but, line);
}
