editToolWin_deinit(EditToolWin *etw)  {
  int  fontH;

  assert(MAGIC(etw));
  if (etw->toolWin != NULL)  {
    fontH = butEnv_fontH(etw->cg->env, 0);
    clp_setInt(etw->cg->clp, "edit.toolX", butWin_x(etw->toolWin));
    clp_setInt(etw->cg->clp, "edit.toolY", butWin_y(etw->toolWin));
    clp_setDouble(etw->cg->clp, "edit.toolW",
		  (double)butWin_w(etw->toolWin) / (double)fontH);
    clp_setDouble(etw->cg->clp, "edit.toolH",
		  (double)butWin_h(etw->toolWin) / (double)fontH);
    butWin_setPacket(etw->toolWin, NULL);
    butWin_destroy(etw->toolWin);
  }
  MAGIC_UNSET(etw);
}
