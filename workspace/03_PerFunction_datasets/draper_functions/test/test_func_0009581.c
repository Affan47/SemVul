qmonCreateProjectAsk(
Widget parent
) {
   Widget project_ok, project_cancel, project_usersPB, project_xusersPB;

   DENTER(GUI_LAYER, "qmonCreateProjectAsk");

   project_ask_layout = XmtBuildQueryDialog( parent, "project_ask_shell",
                           NULL, 0,
                           "project_ok", &project_ok,
                           "project_cancel", &project_cancel,
                           "project_usersPB", &project_usersPB,
                           "project_xusersPB", &project_xusersPB,
                           "project_name", &project_name_w,
                           "project_users", &project_acl_w,
                           "project_xusers", &project_xacl_w,
                           NULL);

   XtAddCallback(project_ok, XmNactivateCallback,
                     qmonProjectOk, NULL);
   XtAddCallback(project_cancel, XmNactivateCallback,
                     qmonProjectCancel, NULL);
   XtAddCallback(project_usersPB, XmNactivateCallback,
                     qmonProjectAskForUsers, (XtPointer)project_acl_w);
   XtAddCallback(project_xusersPB, XmNactivateCallback,
                     qmonProjectAskForUsers, (XtPointer)project_xacl_w);

   XtAddEventHandler(XtParent(project_ask_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);

   DEXIT;
   return project_ask_layout;
}
