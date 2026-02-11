qmonPopupClusterConfig(Widget w, XtPointer cld, XtPointer cad)
{
   Widget shell;
   lList *alp = NULL;

   DENTER(TOP_LAYER, "qmonPopupClusterConfig");


   XmtDisplayBusyCursor(w);

   if (!qmon_cluster) {
      shell = XmtGetTopLevelShell(w);
      qmon_cluster = qmonCreateClusterConfig(shell);
      XmtAddDeleteCallback(shell, XmDO_NOTHING,
                              qmonPopdownClusterConfig, NULL);
   }
   XSync(XtDisplay(qmon_cluster), 0);
   XmUpdateDisplay(qmon_cluster);

   qmonMirrorMultiAnswer(CONFIG_T | EXECHOST_T, &alp);
   if (alp) {
      qmonMessageBox(w, alp, 0);
      lFreeList(&alp);

      XmtDisplayDefaultCursor(w);
      DEXIT;
      return;
   }
   qmonTimerAddUpdateProc(CONFIG_T, "updateClusterList", updateClusterList);
   qmonStartTimer(CONFIG_T | EXECHOST_T);
   updateClusterList();
   XmListSelectPos(cluster_host_list, 1, True);
   XtManageChild(qmon_cluster);
   XRaiseWindow(XtDisplay(XtParent(qmon_cluster)),
                  XtWindow(XtParent(qmon_cluster)));


   XmtDisplayDefaultCursor(w);

   DEXIT;
}
