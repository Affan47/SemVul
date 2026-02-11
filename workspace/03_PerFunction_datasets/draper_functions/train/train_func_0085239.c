cgoban_createHelpWindow(But *but)  {
  Cgoban  *cg;
  const Help  *helpInfo;
  int  x, y, w, h;
  bool  err;

  cg = butEnv_packet(butWin_env(but_win(but)));
  assert(MAGIC(cg));
  helpInfo = but_packet(but);
  assert(helpInfo != NULL);
  if (cg->help)  {
    abutHelp_newPages(cg->help, helpInfo->menuTitle,
		      helpInfo->pages, helpInfo->numPages);
  } else  {
    x = clpEntry_iGetInt(clp_lookup(cg->clp, "help.x"), &err);
    if (err)  {
      x = BUT_NOCHANGE;
      y = BUT_NOCHANGE;
    } else
      y = clp_getInt(cg->clp, "help.y");
    w = (int)(cg->fontH * clp_getDouble(cg->clp, "help.w") + 0.5);
    h = (int)(cg->fontH * clp_getDouble(cg->clp, "help.h") + 0.5);
    cg->help = abutHelp_create(cg->abut, "Cgoban Help",
			       helpInfo->menuTitle,
			       helpInfo->pages,
			       helpInfo->numPages, x, y, w, h,
			       8 * cg->fontH, 8 * cg->fontH);
    abutHelp_setDestroyCallback(cg->help, helpDead, cg);
  }
  return(0);
}
