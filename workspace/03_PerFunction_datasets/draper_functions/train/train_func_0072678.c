qmonOTicketCreate(
Widget parent
) {
   Widget oticket_layout, oticket_cancel, oticket_update,
            oticket_ok, oticket_new, oticket_main_link;

   DENTER(GUI_LAYER, "qmonOTicketCreate");

   oticket_layout = XmtBuildQueryDialog( parent, "qmon_oticket",
                           NULL, 0,
                           "oticket_cancel", &oticket_cancel,
                           "oticket_update", &oticket_update,
                           "oticket_matrix", &oticket_matrix,
                           "oticket_ok", &oticket_ok,
                           "oticket_type", &oticket_type,
                           "oticket_new", &oticket_new,
                           "oticket_main_link", &oticket_main_link,
                           "oticket_message", &oticket_message,
                           NULL);


   oticket_info.layout = oticket_layout;
   oticket_info.matrix = oticket_matrix;

   XtAddCallback(oticket_main_link, XmNactivateCallback,
                     qmonMainControlRaise, NULL);
   XtAddCallback(oticket_cancel, XmNactivateCallback,
                     qmonFOTicketPopdown, (XtPointer)oticket_layout);
   XtAddCallback(oticket_type, XmtNvalueChangedCallback,
                     qmonOTSwitchType, NULL);
   XtAddCallback(oticket_new, XmNactivateCallback,
                     qmonFOTOpenLink, (XtPointer) &oticket_info);
   XtAddCallback(oticket_ok, XmNactivateCallback,
                     qmonOTOkay, NULL);
   XtAddCallback(oticket_update, XmNactivateCallback,
                     qmonOTUpdate, NULL);
   XtAddCallback(oticket_matrix, XmNenterCellCallback,
                     qmonFOTEnterCell, NULL);
   XtAddCallback(oticket_matrix, XmNleaveCellCallback,
                     qmonFOTLeaveCell, NULL);


   XtAddEventHandler(XtParent(oticket_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);

   DEXIT;
   return oticket_layout;
}
