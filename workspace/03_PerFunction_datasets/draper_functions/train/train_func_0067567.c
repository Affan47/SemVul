editInfo_destroy(EditInfo *info, bool propagate)  {
  Cgoban  *cg;

  assert(MAGIC(info));
  if (propagate)  {
    info->destroy(info, info->packet);
    assert(MAGIC(info));
  }
  if (info->win)  {
    cg = info->cg;
    assert(MAGIC(cg));
    clp_setDouble(cg->clp, "edit.infoW",
		  (double)butWin_w(info->win) /
		  (double)butWin_getMinW(info->win));
    clp_setDouble(cg->clp, "edit.infoH",
		  (double)butWin_h(info->win) /
		  (double)butWin_getMinH(info->win));
    clp_setInt(cg->clp, "edit.infoX", butWin_x(info->win));
    clp_setInt(cg->clp, "edit.infoY", butWin_y(info->win));
    butWin_setDestroy(info->win, NULL);
    butWin_destroy(info->win);
  }
  MAGIC_UNSET(info);
  wms_free(info);
}
