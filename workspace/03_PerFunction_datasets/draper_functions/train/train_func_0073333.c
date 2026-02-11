ShowLoadNames(
Widget w,
lList *entries
) {
   lListElem *ep = NULL;
   char stringval[BUFSIZ];
   Boolean status = False;
   String *strs = NULL;
   int n, i;

   DENTER(GUI_LAYER, "ShowLoadNames");

   if (entries) {
      n = lGetNumberOfElem(entries);
      if (n>0) {
         lPSortList(entries, "%I+", CE_name);
         strs = (String*)XtMalloc(sizeof(String)*n);
         for (ep=lFirst(entries), i=0; i<n; ep=lNext(ep), i++) {


           StringConst name = lGetString(ep, CE_name);


           strcpy(stringval, name ? name : "");
           strs[i] = XtNewString(stringval);
         }
      }

      strcpy(stringval, "");
      status = XmtAskForItem(w, NULL, "@{Select an attribute",
                     "@{Available attributes}", strs, n, False,
                     stringval, sizeof(stringval), NULL);


      StringTableFree(strs, n);
   }
   else
      XmtDisplayInformationMsg(w, NULL, "@{No attributes available}",
                                 NULL, NULL);

   if (status) {
      qmonLoadAddEntry(w, stringval);
   }

   DEXIT;
}
