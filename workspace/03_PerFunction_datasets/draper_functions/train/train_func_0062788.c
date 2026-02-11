create_advances_list(struct player *pplayer,
				struct player *pvictim, bool make_modal)
{
  Widget spy_tech_form;
  Widget close_command;
  Dimension width1, width2;
  int j;

  static const char *advances_can_steal[A_LAST+1];

  spy_tech_shell =
    I_T(XtVaCreatePopupShell("spystealtechpopup",
			     (make_modal ? transientShellWidgetClass :
			      topLevelShellWidgetClass),
			     toplevel, NULL));

  spy_tech_form = XtVaCreateManagedWidget("spystealtechform",
					     formWidgetClass,
					     spy_tech_shell,
					     NULL);

  spy_advances_list_label =
    I_L(XtVaCreateManagedWidget("spystealtechlistlabel", labelWidgetClass,
				spy_tech_form, NULL));

  spy_advances_list = XtVaCreateManagedWidget("spystealtechlist",
					      listWidgetClass,
					      spy_tech_form,
					      NULL);

  close_command =
    I_L(XtVaCreateManagedWidget("spystealtechclosecommand", commandWidgetClass,
				spy_tech_form, NULL));

  spy_steal_command =
    I_L(XtVaCreateManagedWidget("spystealtechcommand", commandWidgetClass,
				spy_tech_form,
				XtNsensitive, False,
				NULL));


  XtAddCallback(spy_advances_list, XtNcallback, spy_select_tech_callback, NULL);
  XtAddCallback(close_command, XtNcallback, spy_close_tech_callback, NULL);
  XtAddCallback(spy_steal_command, XtNcallback, spy_steal_callback, NULL);
  XtRealizeWidget(spy_tech_shell);


  j = 0;
  advances_can_steal[j] = _("NONE");
  advance_type[j] = -1;

  if (pvictim) {
    advance_index_iterate(A_FIRST, i) {
      if(player_invention_state(pvictim, i)==TECH_KNOWN &&
         (player_invention_state(pplayer, i)==TECH_UNKNOWN ||
          player_invention_state(pplayer, i)==TECH_PREREQS_KNOWN)) {

        advances_can_steal[j] = advance_name_translation(advance_by_number(i));
        advance_type[j++] = i;
      }
    }
    {
      static struct astring str = ASTRING_INIT;

      astr_set(&str, _("At %s's Discretion"),
               unit_name_translation(game_unit_by_number(diplomat_id)));
      advances_can_steal[j] = astr_str(&str);
      advance_type[j++] = A_UNSET;
    }
  } advance_index_iterate_end;

  if(j == 0) j++;
  advances_can_steal[j] = NULL;

  XtSetSensitive(spy_steal_command, FALSE);

  XawListChange(spy_advances_list, (char **)advances_can_steal, 0, 0, 1);
  XtVaGetValues(spy_advances_list, XtNwidth, &width1, NULL);
  XtVaGetValues(spy_advances_list_label, XtNwidth, &width2, NULL);
  XtVaSetValues(spy_advances_list, XtNwidth, MAX(width1,width2), NULL);
  XtVaSetValues(spy_advances_list_label, XtNwidth, MAX(width1,width2), NULL);

  return j;
}
