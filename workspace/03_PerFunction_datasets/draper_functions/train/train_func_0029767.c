qmonQCProjectToggle(Widget w, XtPointer cld, XtPointer cad)
{
   XmtChooserCallbackStruct *cbs = (XmtChooserCallbackStruct*) cad;

   DENTER(GUI_LAYER, "qmonQCProjectToggle");

   if (cbs->state) {
      XtSetSensitive(project_allow, False);
      XtSetSensitive(project_deny, True);
   }
   else {
      XtSetSensitive(project_allow, True);
      XtSetSensitive(project_deny, False);
   }

   DEXIT;
}
