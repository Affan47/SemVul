GWEN_ProgressData_new(GWEN_GUI *gui,
					  uint32_t id,
					  uint32_t progressFlags,
					  const char *title,
					  const char *text,
					  uint64_t total) {
  GWEN_PROGRESS_DATA *pd;

  GWEN_NEW_OBJECT(GWEN_PROGRESS_DATA, pd);
  GWEN_TREE_INIT(GWEN_PROGRESS_DATA, pd);

  pd->gui=gui;
  pd->id=id;
  pd->flags=progressFlags;
  if (title)
    pd->title=strdup(title);
  if (text)
    pd->text=strdup(text);
  pd->total=total;

  pd->logBuf=GWEN_Buffer_new(0, 1024, 0, 1);
  pd->startTime=time(0);

  return pd;
}
