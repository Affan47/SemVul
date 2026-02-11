checkbox_tool(struct pine *ps, int cmd, CONF_S **cl, unsigned int flags)
{
    int  rv = 0;

    switch(cmd){
      case MC_TOGGLE:
	if((*cl)->var == &ps->vars[V_FEATURE_LIST]){
	    rv = 1;
	    toggle_feature_bit(ps, (*cl)->varmem, (*cl)->var, *cl, 0);
	}
	else
	  q_status_message(SM_ORDER | SM_DING, 3, 6,
			   "Programmer botch!  Unknown checkbox type.");

	break;

      case MC_EXIT:
	rv = config_exit_cmd(flags);
	break;

      default :
	rv = -1;
	break;
    }

    return(rv);
}
