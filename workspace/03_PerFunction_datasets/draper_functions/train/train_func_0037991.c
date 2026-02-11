popup_pillage_dialog(struct unit *punit,
			  bv_special may_pillage,
                          bv_bases bases)
{
  Widget shell, form, dlabel, button, prev;
  int what;

  if (is_showing_pillage_dialog) {
    return;
  }
  is_showing_pillage_dialog = TRUE;
  unit_to_use_to_pillage = punit->id;

  XtSetSensitive (toplevel, FALSE);

  shell = I_T(XtCreatePopupShell("pillagedialog", transientShellWidgetClass,
				 toplevel, NULL, 0));
  form = XtVaCreateManagedWidget ("form", formWidgetClass, shell, NULL);
  dlabel = I_L(XtVaCreateManagedWidget("dlabel", labelWidgetClass, form, NULL));

  prev = dlabel;
  while ((what = get_preferred_pillage(may_pillage, bases)) != S_LAST) {
    bv_special what_bv;
    bv_bases what_base;

    BV_CLR_ALL(what_bv);
    BV_CLR_ALL(what_base);

    if (what > S_LAST) {
      BV_SET(what_base, what % (S_LAST + 1));
    } else {
      BV_SET(what_bv, what);
    }

    button =
      XtVaCreateManagedWidget ("button", commandWidgetClass, form,
                               XtNfromVert, prev,
                               XtNlabel,
                               (XtArgVal)(get_infrastructure_text(what_bv,
                                                                  what_base)),
                               NULL);
    XtAddCallback(button, XtNcallback, pillage_callback,
                  INT_TO_XTPOINTER(what));

    if (what > S_LAST) {
      BV_CLR(bases, what - S_LAST - 1);
    } else {
      clear_special(&may_pillage, what);
    }
    prev = button;
  }
  button =
    I_L(XtVaCreateManagedWidget("closebutton", commandWidgetClass, form,
				XtNfromVert, prev,
				NULL));
  XtAddCallback (button, XtNcallback, pillage_callback, NULL);

  xaw_set_relative_position (toplevel, shell, 10, 0);
  XtPopup (shell, XtGrabNone);
}
