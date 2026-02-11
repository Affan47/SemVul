GWEN_Gui_Internal_ProgressAdvance(GWEN_GUI *gui, uint32_t pid, uint64_t progress) {
  GWEN_PROGRESS_DATA *pd;
  int aborted=0;

  if (pid==0) {
    pid=gui->lastProgressId;
    if (pid==0) {
      DBG_INFO(GWEN_LOGDOMAIN, "Last active progress not available");
      return GWEN_ERROR_INVALID;
    }
  }

  pd=GWEN_ProgressData_Tree_FindProgressById(gui->progressDataTree, pid);
  if (pd==NULL) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Progress by id %08x not found", pid);
    return GWEN_ERROR_INVALID;
  }
  else {
    GWEN_DIALOG *dlg;

    if (progress==GWEN_GUI_PROGRESS_ONE)
      progress=GWEN_ProgressData_GetCurrent(pd)+1;
    else if (progress==GWEN_GUI_PROGRESS_NONE)
      progress=GWEN_ProgressData_GetCurrent(pd);
    GWEN_ProgressData_SetCurrent(pd, progress);
    GWEN_Gui_Internal_CheckShow(gui, pd);

    dlg=GWEN_ProgressData_GetDialog(pd);
    if (dlg) {
      time_t t0;
      time_t t1;

      t0=GWEN_ProgressData_GetCheckTime(pd);
      t1=time(0);
      if (t0!=t1) {
	GWEN_DlgProgress_Advanced(dlg, pd);
	GWEN_Gui_RunDialog(dlg, 0);
	GWEN_ProgressData_SetCheckTime(pd, t1);
      }
    }
    aborted=GWEN_ProgressData_GetAborted(pd);
  }

  if (aborted)
    return GWEN_ERROR_USER_ABORTED;
  return 0;
}
