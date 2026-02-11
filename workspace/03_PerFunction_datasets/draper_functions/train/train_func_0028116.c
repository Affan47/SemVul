qmonUsersetFillConf(
Widget w,
lListElem *ep
) {
   lList *ul;

   DENTER(GUI_LAYER, "qmonUsersetFillConf");

   if (!ep) {


      XtVaSetValues( userset_user_list,
                  XmNitems, NULL,
                  XmNitemCount, 0,
                  NULL);
      DEXIT;
      return;
   }

   userset_type_state = (int)lGetUlong(ep, US_type);
   XmtChooserSetState(userset_type, userset_type_state, False);
   ul = lGetList(ep, US_entries);
   lPSortList(ul, "%I+", UE_name);
   UpdateXmListFromCull(userset_user_list, XmFONTLIST_DEFAULT_TAG, ul, UE_name);

   DEXIT;
}
