directory_config(struct pine *ps, int edit_exceptions)
{
    CONF_S   *ctmp = NULL, *first_line = NULL;
    OPT_SCREEN_S  screen;
    int           no_ex, readonly_warning = 0;

    if(edit_exceptions){
	q_status_message(SM_ORDER, 3, 7,
			 _("Exception Setup not implemented for directory"));
	return;
    }

    ew = edit_exceptions ? ps_global->ew_for_except_vars : Main;

    no_ex = (ps_global->ew_for_except_vars == Main);

    if(ps->restricted)
      readonly_warning = 1;
    else{
	PINERC_S *prc = NULL;

	switch(ew){
	  case Main:
	    prc = ps->prc;
	    break;
	  case Post:
	    prc = ps->post_prc;
	    break;
	  default:
	    break;
	}

	readonly_warning = prc ? prc->readonly : 1;
	if(prc && prc->quit_to_edit){
	    quit_to_edit_msg(prc);
	    return;
	}
    }

    if(ps->fix_fixed_warning)
      offer_to_fix_pinerc(ps);

    dir_init_display(ps, &ctmp, no_ex ? ps->VAR_LDAP_SERVERS
				      : LVAL(&ps->vars[V_LDAP_SERVERS], ew),
		     &ps->vars[V_LDAP_SERVERS], &first_line);

    memset(&screen, 0, sizeof(screen));
    screen.deferred_ro_warning = readonly_warning;


    (void)conf_scroll_screen(ps, &screen, first_line,
			     _("SETUP DIRECTORY SERVERS"), _("servers"), 0);
    ps->mangled_screen = 1;
}
