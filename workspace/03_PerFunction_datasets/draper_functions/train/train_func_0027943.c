qmonCreateManopConfig(
Widget parent
) {
   Widget manop_layout, manop_add, manop_delete, manop_done, manop_help,
          manop_main_link, user_layout, manop_tickets;

   DENTER(GUI_LAYER, "qmonCreateManopConfig");

   manop_layout = XmtBuildQueryDialog( parent, "qmon_manop",
                           NULL, 0,
                           "manop_folder", &manop_folder,
                           "manop_add", &manop_add,
                           "manop_modify", &manop_modify,
                           "manop_tickets", &manop_tickets,
                           "manop_delete", &manop_delete,
                           "manop_done", &manop_done,
                           "manop_help", &manop_help,
                           "manop_main_link", &manop_main_link,
                           "manager_list", &manager_list,
                           "manager_name", &manager_name,
                           "operator_list", &operator_list,
                           "operator_name", &operator_name,
                           NULL);

   userset_layout = qmonCreateUsersetConfig(manop_folder, NULL);
   XtManageChild(userset_layout);

   user_layout = qmonCreateUserConfig(manop_folder, NULL);
   XtAddCallback(manop_tickets, XmNactivateCallback,
                     qmonPopupTicketOverview, NULL);

   XtAddCallback(manop_main_link, XmNactivateCallback,
                     qmonMainControlRaise, NULL);
   XtAddCallback(manop_folder, XmNvalueChangedCallback,
                     qmonManopFolderChange, NULL);
   XtAddCallback(manop_done, XmNactivateCallback,
                     qmonPopdownManopConfig, NULL);
   XtAddCallback(manop_add, XmNactivateCallback,
                     qmonManopAdd, (XtPointer) 1);
   XtAddCallback(manop_modify, XmNactivateCallback,
                     qmonManopAdd, NULL);
   XtAddCallback(manager_name, XmNactivateCallback ,
                     qmonManopAdd, NULL);
   XtAddCallback(operator_name, XmNactivateCallback ,
                     qmonManopAdd, NULL);
   XtAddCallback(manop_delete, XmNactivateCallback,
                     qmonManopDelete, NULL);
   XtAddCallback(manop_help, XmNactivateCallback,
                     qmonManopHelp, NULL);

   XtAddEventHandler(XtParent(manop_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);

   DEXIT;
   return manop_layout;
}
