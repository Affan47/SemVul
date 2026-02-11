qmonPEAskForUsers(Widget w, XtPointer cld, XtPointer cad)
{
   lList *ql_out = NULL;
   lList *ql_in = NULL;
   int status;
   Widget list = (Widget) cld;

   DENTER(GUI_LAYER, "qmonPEAskForUsers");

   ql_in = qmonMirrorList(SGE_US_LIST);
   ql_out = XmStringToCull(list, US_Type, US_name, ALL_ITEMS);

   status = XmtAskForItems(w, NULL, NULL, "@{Select Access Lists}", ql_in, US_name,
                  "@{@fBAvailable Access Lists}", &ql_out, US_Type, US_name,
                  "@{@fBChosen Access Lists}", NULL);

   if (status) {
      UpdateXmListFromCull(list, XmFONTLIST_DEFAULT_TAG, ql_out,
                              US_name);
   }
   lFreeList(&ql_out);

   DEXIT;
}
