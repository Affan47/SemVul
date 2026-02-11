qmonShareTreeShowMore(Widget w, XtPointer cld, XtPointer cad)
{
   static Boolean managed = False;
   Widget ratio = (Widget)cld;
   static Pixmap open;
   static Pixmap closed;

   DENTER(GUI_LAYER, "qmonShareTreeShowMore");

   if (!open) {
      open = qmonGetIcon("leftarrow");
      closed = qmonGetIcon("rightarrow");
   }

   if (!managed) {
      managed = True;
      XtVaSetValues(w, XmNlabelPixmap, open, NULL);
      XtManageChild(ratio);
   }
   else {
      managed = False;
      XtVaSetValues(w, XmNlabelPixmap, closed, NULL);
      XtUnmanageChild(ratio);
   }

   DEXIT;
}
