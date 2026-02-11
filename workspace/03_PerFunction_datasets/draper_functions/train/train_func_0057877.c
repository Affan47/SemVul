qmonExecHostAccessRemove(Widget w, XtPointer cld, XtPointer cad)
{
   XmString *selectedItems;
   Cardinal selectedItemCount;
   int state;
   Widget list;

   DENTER(GUI_LAYER, "qmonExecHostAccessRemove");

   state = XmtChooserGetState(access_toggle);

   if (state)
      list = access_deny;
   else
      list = access_allow;

   XtVaGetValues( list,
                  XmNselectedItems, &selectedItems,
                  XmNselectedItemCount, &selectedItemCount,
                  NULL);

   if (selectedItemCount)
      XmListDeleteItems(list, selectedItems, selectedItemCount);

   DEXIT;
}
