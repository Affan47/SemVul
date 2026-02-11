qmonPopdownCplxConfig(Widget w, XtPointer cld, XtPointer cad)
{
   DENTER(GUI_LAYER, "qmonPopdownCplxConfig");

   XtUnmanageChild(qmon_cplx);
   XtPopdown(XtParent(qmon_cplx));

   DEXIT;
}
