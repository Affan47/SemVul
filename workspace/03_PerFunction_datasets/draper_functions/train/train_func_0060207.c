qmonExecHostReportVarAdd(Widget w, XtPointer cld, XtPointer cad)
{
   XmString *selectedItems;
   Cardinal selectedItemCount, i;
   String text;

   DENTER(GUI_LAYER, "qmonExecHostReportVarAdd");

   XtVaGetValues( reporting_variables_list,
                  XmNselectedItems, &selectedItems,
                  XmNselectedItemCount, &selectedItemCount,
                  NULL);

   if (selectedItemCount) {
      for (i=0; i<selectedItemCount; i++) {
         if (!XmStringGetLtoR(selectedItems[i], XmFONTLIST_DEFAULT_TAG, &text))
            continue;
         XmListAddItemUniqueSorted(reporting_variables_chosen, text);
         XtFree(text);
      }
   }

   DEXIT;
}
