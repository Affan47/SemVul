qmonSubmitCheckInput(Widget w, XtPointer cld, XtPointer cad)
{
   XmtInputFieldCallbackStruct *cbs = (XmtInputFieldCallbackStruct*)cad;

   DENTER(GUI_LAYER, "qmonSubmitCheckInput");

   if (!cbs->input || *(cbs->input) == '\0')
      qmonSubmitClear(w, NULL, NULL);

   DEXIT;
}
