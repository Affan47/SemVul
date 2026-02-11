context_config_tool(struct pine *ps, int cmd, CONF_S **cl, unsigned int flags)
{
    int retval = 0;

    switch(cmd){
      case MC_DELETE :
	if(!fixed_var((*cl)->var, "delete", "collection"))
	  retval = context_config_delete(ps, cl);

	break;

      case MC_EDIT :
	if(!fixed_var((*cl)->var, "change", "collection"))
	  retval = context_config_edit(ps, cl);

	break;

      case MC_ADD :
	if(!fixed_var((*cl)->var, "add to", "collection"))
	  retval = context_config_add(ps, cl);

	break;

      case MC_SHUFFLE :
	if(!fixed_var((*cl)->var, "shuffle", "collection"))
	  retval = context_config_shuffle(ps, cl);

	break;

      case MC_EXIT :
        retval = simple_exit_cmd(flags);
	break;

      default:
	retval = -1;
	break;
    }

    if(retval > 0)
      ps->mangled_body = 1;

    return(retval);
}
