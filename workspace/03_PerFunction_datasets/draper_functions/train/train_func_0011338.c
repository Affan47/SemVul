butList_setLen(But *but, int newLen)  {
  List  *list = but->iPacket;
  int  i;
  ListEl  *newLines;

  assert(MAGIC(list));
  if (newLen > list->maxLines)  {
    newLines = wms_malloc(newLen * sizeof(ListEl));
    for (i = 0;  i < list->maxLines;  ++i)  {
      newLines[i] = list->lines[i];
    }
    for (;  i < newLen;  ++i)  {
      newLines[i].pressable = FALSE;
      str_init(&newLines[i].str);
    }
    wms_free(list->lines);
    list->maxLines = newLen;
    list->lines = newLines;
  }
  if (newLen > list->numLines)  {
    for (i = list->numLines;  i < newLen;  ++i)  {
      str_copyCharsLen(&list->lines[i].str, "", 0);
      list->lines[i].pressable = FALSE;
    }
  }
  list->numLines = newLen;
  butList_resize(but, but->x, but->y, but->w);
}
