qmonRequestOkay(Widget w, XtPointer cld, XtPointer cad)
{

   DENTER(GUI_LAYER, "qmonRequestOkay");

   xmui_unmanage(request_dialog);


   qmonSubmitSetResources(&hard_requests, &soft_requests);


   DEXIT;
}
