popup_races_dialog(struct player *pplayer)
{
  Position x, y;
  Dimension width, height;

  XtSetSensitive(main_form, FALSE);

  if (!races_dialog_shell) {
    create_races_dialog(pplayer);
  }

  XtVaGetValues(toplevel, XtNwidth, &width, XtNheight, &height, NULL);

  XtTranslateCoords(toplevel, (Position) width/20, (Position) height/20,
		    &x, &y);
  XtVaSetValues(races_dialog_shell, XtNx, x, XtNy, y, NULL);

  XtPopup(races_dialog_shell, XtGrabNone);
  XtSetKeyboardFocus(toplevel, races_dialog_shell);
}
