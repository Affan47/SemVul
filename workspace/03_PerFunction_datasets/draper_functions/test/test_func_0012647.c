folder_lister_addmanually(SCROLL_S *sparms)
{
    int        rc, flags = OE_APPEND_CURRENT, cnt = 0, rv = 0;
    char       addname[MAXFOLDER+1];
    HelpType   help;
    CONTEXT_S *cntxt = (sparms->text.handles)
			 ? sparms->text.handles->h.f.context
			 : FPROC(sparms)->fs->context;


    addname[0] = '\0';
    help = NO_HELP;
    while(1){
	rc = optionally_enter(addname, -FOOTER_ROWS(ps_global), 0,
			      sizeof(addname), _("Name of new folder : "),
			      NULL, help, &flags);
	removing_leading_and_trailing_white_space(addname);

	if(rc == 3)
	  help = (help == NO_HELP) ? h_save_addman : NO_HELP;
	else if(rc == 1)
	  return(rv);
	else if(rc == 0){
	    if(F_OFF(F_ENABLE_DOT_FOLDERS,ps_global) && *addname == '.'){
		if(cnt++ <= 0)
                  q_status_message(SM_ORDER,3,3,
		    _("Folder name can't begin with dot"));
		else
		  q_status_message1(SM_ORDER,3,3,
		   _("Config feature \"%s\" enables names beginning with dot"),
		   pretty_feature_name(feature_list_name(F_ENABLE_DOT_FOLDERS), -1));

                display_message(NO_OP_COMMAND);
                continue;
	    }
	    else if(!strucmp(addname, ps_global->inbox_name)){
		q_status_message1(SM_ORDER, 3, 3,
				  _("Can't add folder named %s"),
				  ps_global->inbox_name);
		continue;
	    }

	    break;
	}
    }

    if(*addname){
	FPROC(sparms)->fs->context = cntxt;
	FPROC(sparms)->rv = new_strlist(NULL);
	FPROC(sparms)->rv->name = folder_lister_fullname(FPROC(sparms)->fs,
							 addname);
	FPROC(sparms)->done = rv = 1;
    }

    return(rv);
}
