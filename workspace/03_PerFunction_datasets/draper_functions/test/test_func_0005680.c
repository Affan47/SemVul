qmonQCPEAdd(Widget w, XtPointer cld, XtPointer cad)
{
   XmString *selectedItems;
   Cardinal selectedItemCount, i;
   String text;

   DENTER(GUI_LAYER, "qmonQCPEAdd");

   XtVaGetValues( pe_list,
                  XmNselectedItems, &selectedItems,
                  XmNselectedItemCount, &selectedItemCount,
                  NULL);

   if (selectedItemCount) {
      XmtLayoutDisableLayout(cq_dialog);

      for (i=0; i<selectedItemCount; i++) {
         if (!XmStringGetLtoR(selectedItems[i], XmFONTLIST_DEFAULT_TAG, &text))
            continue;
         XmListAddItemUniqueSorted(pe_reference_list, text);
         XtFree(text);
      }
      XmtLayoutEnableLayout(cq_dialog);
   }

   DEXIT;
}
