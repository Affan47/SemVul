qmonPEFilterSet(Widget w, XtPointer cld, XtPointer cad)
{
   lList *apl = NULL;

   DENTER(GUI_LAYER, "qmonPEFilterSet");

   apl = qmonMirrorList(SGE_PE_LIST);
   UpdateXmListFromCull(pe_filter_ap, XmFONTLIST_DEFAULT_TAG, apl, PE_name);
   UpdateXmListFromCull(pe_filter_sp, XmFONTLIST_DEFAULT_TAG,
                           queue_filter_pe, ST_name);

   DEXIT;
}
