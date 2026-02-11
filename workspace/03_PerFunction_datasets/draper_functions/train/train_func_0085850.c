mta_handoff(METAENV *header, struct mail_bodystruct *body,
	    char *errbuf, size_t len,
	    void (*bigresult_f) (char *, int),
	    void (*pipecb_f)(PIPE_S *, int, void *))
{
#ifdef	DF_SENDMAIL_PATH
    char  cmd_buf[256];
#endif
    char *cmd = NULL;


    if(ps_global->FIX_SENDMAIL_PATH
       && ps_global->FIX_SENDMAIL_PATH[0]){
	cmd = ps_global->FIX_SENDMAIL_PATH;
    }
    else if(!(ps_global->FIX_SMTP_SERVER
	      && ps_global->FIX_SMTP_SERVER[0])){
	if(ps_global->COM_SENDMAIL_PATH
	   && ps_global->COM_SENDMAIL_PATH[0]){
	    cmd = ps_global->COM_SENDMAIL_PATH;
	}
	else if(!(ps_global->COM_SMTP_SERVER
		  && ps_global->COM_SMTP_SERVER[0])){
	    if((ps_global->vars[V_SENDMAIL_PATH].post_user_val.p
	        && ps_global->vars[V_SENDMAIL_PATH].post_user_val.p[0]) ||
	       (ps_global->vars[V_SENDMAIL_PATH].main_user_val.p
	        && ps_global->vars[V_SENDMAIL_PATH].main_user_val.p[0])){
		if(ps_global->vars[V_SENDMAIL_PATH].post_user_val.p
		   && ps_global->vars[V_SENDMAIL_PATH].post_user_val.p[0])
		  cmd = ps_global->vars[V_SENDMAIL_PATH].post_user_val.p;
		else
		  cmd = ps_global->vars[V_SENDMAIL_PATH].main_user_val.p;
	    }
	    else if(!((ps_global->vars[V_SMTP_SERVER].post_user_val.l
	               && ps_global->vars[V_SMTP_SERVER].post_user_val.l[0]) ||
		      (ps_global->vars[V_SMTP_SERVER].main_user_val.l
	               && ps_global->vars[V_SMTP_SERVER].main_user_val.l[0]))){
		if(ps_global->GLO_SENDMAIL_PATH
		   && ps_global->GLO_SENDMAIL_PATH[0]){
		    cmd = ps_global->GLO_SENDMAIL_PATH;
		}
#ifdef	DF_SENDMAIL_PATH


		else if(!(ps_global->GLO_SMTP_SERVER
			  && ps_global->GLO_SMTP_SERVER[0])){
		    strncpy(cmd = cmd_buf, DF_SENDMAIL_PATH, sizeof(cmd_buf)-1);
		    cmd_buf[sizeof(cmd_buf)-1] = '\0';
		}
#endif
	    }
	}
    }

    *errbuf = '\0';
    if(cmd){
	dprint((4, "call_mailer via cmd: %s\n", cmd ? cmd : "?"));

	(void) mta_parse_post(header, body, cmd, errbuf, len, bigresult_f, pipecb_f);
	return(1);
    }
    else
      return(0);
}
