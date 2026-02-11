qmonARSubCreateDialogs(
Widget w
) {
   Widget armatrix, arreset, arcancel, arokay, ardelete,
          armail_list_new;

   DENTER(GUI_LAYER, "qmonARSubCreateDialogs");


   if (!armail_list_w) {
      armail_list_w = XmtBuildQueryDialog( w,
                                       "arsub_mail_list_shell",
                                       arsm_resources, XtNumber(arsm_resources),
                                       "armail_list_matrix", &armatrix,
                                       "armail_list_cancel", &arcancel,
                                       "armail_list_okay", &arokay,
                                       "armail_list_reset", &arreset,
                                       "armail_list_delete", &ardelete,
                                       "armail_list_new", &armail_list_new,
                                       NULL
                                       );
      XtRealizeWidget(armail_list_w);

      XtAddCallback(arreset, XmNactivateCallback,
                     qmonARSubReset, (XtPointer) armail_list_w);
      XtAddCallback(arokay, XmNactivateCallback,
                     qmonARSubOkay, (XtPointer) armail_list_w);
      XtAddCallback(arcancel, XmNactivateCallback,
                     qmonARSubCancel, (XtPointer) armail_list_w);
      XtAddCallback(ardelete, XmNactivateCallback,
                     qmonARSubDelete, (XtPointer) armatrix);
      XtAddCallback(armail_list_new, XmtNinputCallback,
                     qmonARSubMailInput, (XtPointer) armatrix);

   }

   DEXIT;
}
