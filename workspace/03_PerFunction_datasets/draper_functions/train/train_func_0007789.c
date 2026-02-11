qmonARSubCreate(
Widget parent
) {
   Widget arsub_handle_hard_error;

   DENTER(GUI_LAYER, "qmonARSubCreate");


   arsub_layout = XmtBuildQueryDialog( parent, "qmon_arsub",
                          arsm_resources, XtNumber(arsm_resources),
                          "arsub_mail_userPB", &arsub_mail_userPB,
                          "arsub_pePB", &arsub_pePB,
                          "arsub_queue_listPB", &arsub_queue_listPB,
                          "arsub_master_queue_listPB", &arsub_master_queue_listPB,
                          "arsub_arsub", &arsub_arsub,
                          "arsub_done", &arsub_done,
                          "arsub_resources", &arsub_resources,
                          "arsub_access", &arsub_access,
                          "arsub_xaccess", &arsub_xaccess,
                          "arsub_accessPB", &arsub_accessPB,
                          "arsub_xaccessPB", &arsub_xaccessPB,
                          "arsub_mail", &arsub_mail,
                          "arsub_mail_user", &arsub_mail_user,
                          "arsub_pe", &arsub_pe,
                          "arsub_queue_list", &arsub_queue_list,
                          "arsub_master_queue_list", &arsub_master_queue_list,
                          "arsub_start_time", &arsub_start_time,
                          "arsub_start_timePB", &arsub_start_timePB,
                          "arsub_end_time", &arsub_end_time,
                          "arsub_end_timePB", &arsub_end_timePB,
                          "arsub_duration_row", &arsub_duration_row,
                          "arsub_duration", &arsub_duration,
                          "arsub_durationPB", &arsub_durationPB,
                          "arsub_duration_toggle", &arsub_duration_toggle,
                          "arsub_handle_hard_error", &arsub_handle_hard_error,
                          "arsub_now", &arsub_now,
                          "arsub_ckpt_obj", &arsub_ckpt_obj,
                          "arsub_ckpt_objPB", &arsub_ckpt_objPB,
                          "arsub_clear", &arsub_clear,
                          "arsub_name", &arsub_name,
                          "arsub_main_link", &arsub_main_link,
                          "arsub_message", &arsub_message,
                          NULL);


   XtAddCallback(arsub_durationPB, XmNactivateCallback,
                  qmonARSubDuration, (XtPointer)arsub_duration);
   XtManageChild(arsub_layout);


   XtAddCallback(arsub_main_link, XmNactivateCallback,
                     qmonMainControlRaise, NULL);
   XtAddCallback(arsub_name, XmtNverifyCallback,
                     qmonARSubCheckARName, NULL);
   XtAddCallback(arsub_arsub, XmNactivateCallback,
                     qmonARSubARSub, NULL);
   XtAddCallback(arsub_resources, XmNactivateCallback,
                     qmonPopupARSubResource, NULL);
   XtAddCallback(arsub_accessPB, XmNactivateCallback,
                     qmonPopupARSubAccess, (XtPointer)arsub_access);
   XtAddCallback(arsub_xaccessPB, XmNactivateCallback,
                     qmonPopupARSubAccess, (XtPointer)arsub_xaccess);
   XtAddCallback(arsub_done, XmNactivateCallback,
                     qmonARSubPopdown, NULL);
   XtAddCallback(arsub_clear, XmNactivateCallback,
                     qmonARSubClear, NULL);
   XtAddCallback(arsub_mail_userPB, XmNactivateCallback,
                     qmonARSubMailList, NULL);
   XtAddCallback(arsub_ckpt_objPB, XmNactivateCallback,
                     qmonARSubAskForCkpt, NULL);
   XtAddCallback(arsub_pePB, XmNactivateCallback,
                     qmonARSubAskForPE, NULL);
   XtAddCallback(arsub_queue_listPB, XmNactivateCallback,
                     qmonARSubAskForCQ, (XtPointer)arsub_queue_list);
   XtAddCallback(arsub_master_queue_listPB, XmNactivateCallback,
                     qmonARSubAskForCQ, (XtPointer)arsub_master_queue_list);
   XtAddCallback(arsub_start_timePB, XmNactivateCallback,
                     qmonARSubStartEndTime, (XtPointer) arsub_start_time);
   XtAddCallback(arsub_end_timePB, XmNactivateCallback,
                     qmonARSubStartEndTime, (XtPointer) arsub_end_time);
   XtAddCallback(arsub_duration_toggle, XmNvalueChangedCallback,
                     qmonARSubToggleDuration, NULL);

   XtAddEventHandler(XtParent(arsub_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);
   XtAddEventHandler(XtParent(arsub_layout), StructureNotifyMask, False,
                        SetMaxShellSize, NULL);

   DEXIT;
   return arsub_layout;

}
