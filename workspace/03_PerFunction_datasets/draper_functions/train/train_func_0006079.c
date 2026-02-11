wDestroy(ButWin *win)  {
  AbutFsel  *f = butWin_packet(win);

  assert(MAGIC(f));
  if (f->abut->clp)  {
    clp_setInt(f->abut->clp, "abut.fsel.x", butWin_x(win));
    clp_setInt(f->abut->clp, "abut.fsel.y", butWin_y(win));
    clp_setDouble(f->abut->clp, "abut.fsel.w",
		  (double)butWin_w(win) / (double)butWin_getMinW(win));
    clp_setDouble(f->abut->clp, "abut.fsel.h",
		  (double)butWin_h(win) / (double)butWin_getMinH(win));
  }
  if (f->callback && f->propagate)  {
    f->callback(f, f->packet, NULL);
    f->callback = NULL;
  }
  abutSwin_destroy(f->dSwin);
  abutSwin_destroy(f->fSwin);
  str_deinit(&f->pathVal);
  if (f->msg)  {
    abutMsg_destroy(f->msg, FALSE);
    f->msg = NULL;
  }
  MAGIC_UNSET(f);
  wms_free(f);
  return(0);
}
