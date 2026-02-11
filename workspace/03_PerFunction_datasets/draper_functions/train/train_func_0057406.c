qmonCkptAdd(Widget w, XtPointer cld, XtPointer cad)
{
   DENTER(GUI_LAYER, "qmonCkptAdd");

   qmonCkptResetAsk();
   XtVaSetValues( ckpt_name_w,
                  XmNeditable, True,
                  NULL);
   add_mode = 1;
   XtManageChild(ckpt_ask_layout);

   DEXIT;
}
