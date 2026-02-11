cmd_take_addr(struct pine *ps, MSGNO_S *msgmap, int agg)
{
    TA_S *ta_list = NULL;
    int  how_many_selected = 0, rtype;


    if(!agg && F_ON(F_ENABLE_ROLE_TAKE, ps)){
	rtype = rule_setup_type(ps,
				RS_RULES |
				  ((mn_get_total(msgmap) > 0)
				    ? (F_ON(F_ENABLE_TAKE_EXPORT, ps)
				       ? (RS_INCADDR | RS_INCEXP)
				       : RS_INCADDR)
				    : RS_NONE),
				"Take to : ");
    }
    else if(F_ON(F_ENABLE_TAKE_EXPORT, ps) && mn_get_total(msgmap) > 0)
      rtype = rule_setup_type(ps, RS_INCADDR | RS_INCEXP, "Take to : ");
    else
      rtype = 'a';

    if(rtype == 'x' || rtype == 'Z'){
	if(rtype == 'x')
	  cmd_cancelled(NULL);
	else if(rtype == 'Z')
	  q_status_message(SM_ORDER | SM_DING, 3, 5,
			   "Try turning on color with the Setup/Kolor command.");
	return -1;
    }

    ps->mangled_footer = 1;

    if(rtype > 0)
      switch(rtype){
	case 'e':
	  {
	      LINES_TO_TAKE *lines_to_take = NULL;

	      rtype = set_up_takeaddr('e', ps, msgmap, &ta_list, &how_many_selected,
				      agg ? TA_AGG : 0, NULL);

	      if(rtype >= 0){
		  if(convert_ta_to_lines(ta_list, &lines_to_take)){
		      while(lines_to_take && lines_to_take->prev)
			lines_to_take = lines_to_take->prev;

		      take_to_export(ps, lines_to_take);

		      free_ltlines(&lines_to_take);
		  }
		  else
		    q_status_message(SM_ORDER, 3, 4, _("Can't find anything to export"));
	      }
	  }

	  break;

	case 'r':
	case 's':
	case 'i':
	case 'f':
	case 'o':
	case 'c':
	case 'x':
	  role_take(ps, msgmap, rtype);
	  break;

	case 'a':
	  rtype = set_up_takeaddr('a', ps, msgmap, &ta_list, &how_many_selected,
				  agg ? TA_AGG : 0, attached_addr_handler);
	  if(rtype >= 0){
	      (void) takeaddr_screen(ps, ta_list, how_many_selected,
				     agg ? ListMode : SingleMode,
				     NULL, _("take"));
	  }

	  break;

	default:
	  break;
      }


    free_talines(&ta_list);
    env_for_pico_callback   = NULL;
    body_for_pico_callback  = NULL;

    return(rtype >= 0 ? 1 : 0);
}
