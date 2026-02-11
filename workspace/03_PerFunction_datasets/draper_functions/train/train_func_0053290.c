popup_goto_dialog(void)
{
  Position x, y;
  Dimension width, height;
  Boolean no_player_cities;

  if (!can_client_issue_orders() || get_num_units_in_focus() == 0) {
    return;
  }

  no_player_cities = !(city_list_size(client.conn.playing->cities));

  original_tile = get_center_tile_mapcanvas();

  XtSetSensitive(main_form, FALSE);

  goto_dialog_shell =
    I_T(XtCreatePopupShell("gotodialog", transientShellWidgetClass,
			   toplevel, NULL, 0));

  goto_form = XtVaCreateManagedWidget("gotoform",
				      formWidgetClass,
				      goto_dialog_shell, NULL);

  goto_label =
    I_L(XtVaCreateManagedWidget("gotolabel", labelWidgetClass,
				goto_form, NULL));

  goto_viewport = XtVaCreateManagedWidget("gotoviewport",
				      viewportWidgetClass,
				      goto_form,
				      NULL);

  goto_list = XtVaCreateManagedWidget("gotolist",
				      listWidgetClass,
				      goto_viewport,
				      XtNlist,
				      (XtArgVal)dummy_city_list,
				      NULL);

  goto_center_command =
    I_L(XtVaCreateManagedWidget("gotocentercommand", commandWidgetClass,
				goto_form, NULL));

  goto_airlift_command =
    I_L(XtVaCreateManagedWidget("gotoairliftcommand", commandWidgetClass,
				goto_form, NULL));

  goto_all_toggle =
    I_L(XtVaCreateManagedWidget("gotoalltoggle", toggleWidgetClass,
				goto_form,
				XtNstate, no_player_cities,
				XtNsensitive, !no_player_cities,
				NULL));

  goto_cancel_command =
    I_L(XtVaCreateManagedWidget("gotocancelcommand", commandWidgetClass,
				goto_form, NULL));

  XtAddCallback(goto_list, XtNcallback, goto_list_callback, NULL);
  XtAddCallback(goto_center_command, XtNcallback,
		goto_goto_command_callback, NULL);
  XtAddCallback(goto_airlift_command, XtNcallback,
		goto_airlift_command_callback, NULL);
  XtAddCallback(goto_all_toggle, XtNcallback,
		goto_all_toggle_callback, NULL);
  XtAddCallback(goto_cancel_command, XtNcallback,
		goto_cancel_command_callback, NULL);

  XtRealizeWidget(goto_dialog_shell);

  update_goto_dialog(goto_list);

  XtVaGetValues(toplevel, XtNwidth, &width, XtNheight, &height, NULL);

  XtTranslateCoords(toplevel, (Position) width/10, (Position) height/10,
		    &x, &y);
  XtVaSetValues(goto_dialog_shell, XtNx, x, XtNy, y, NULL);

  XtPopup(goto_dialog_shell, XtGrabNone);


  XtVaSetValues(goto_viewport, XtNforceBars, True, NULL);
}
