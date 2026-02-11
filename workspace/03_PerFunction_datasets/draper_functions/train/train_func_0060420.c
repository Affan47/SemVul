wquit(int f, int n)
{
    register int    s;

    if(Pmaster){
	char *result = NULL;
	int   ret;


	if(AttachError()){
	    emlwrite(_("\007Problem with attachments!  Fix errors or delete attachments."), NULL);
	    return(FALSE);
	}

#ifdef	SPELLER
	if(Pmaster->always_spell_check)
	  if(spell(0, 0) == -1)
	    sleep(3);
#endif


	display_for_send();
	packheader();
	Pmaster->arm_winch_cleanup++;
	if((!(Pmaster->pine_flags & MDHDRONLY) || any_header_changes())
	   && (ret = (*Pmaster->exittest)(Pmaster->headents,
					     redraw_pico_for_callback,
					     Pmaster->allow_flowed_text,
					     &result))){
	    Pmaster->arm_winch_cleanup--;

	    if(ret == -1){
		pico_all_done = COMP_CANCEL;
	    }
	    else{
		if(sgarbf)
		  update();

		lchange(WFHARD);
		curwp->w_flag |= WFMODE;
		sgarbk = TRUE;
		pclear(term.t_nrow-2, term.t_nrow);
	    }

	    if(result && *result)
	      emlwrite(result, NULL);
	}
	else{
	    Pmaster->arm_winch_cleanup--;
	    pico_all_done = COMP_EXIT;
	    return(TRUE);
	}
    }
    else{
        if (f != FALSE
        || anycb() == FALSE


        || (s=mlyesno_utf8(_("Save modified buffer (ANSWERING \"No\" WILL DESTROY CHANGES)"), -1)) == FALSE) {
                vttidy();
#if     defined(USE_TERMCAP) || defined(USE_TERMINFO) || defined(VMS)
		kbdestroy(kbesc);
#endif
                exit(0);
        }

	if(s == TRUE){
	    if(filewrite(0,1) == TRUE)
	      wquit(1, 0);
	}
	else if(s == ABORT){
	    emlwrite(_("Exit cancelled"), NULL);
	    if(term.t_mrow == 0)
	      curwp->w_flag |= WFHARD;
	}
        return(s);
    }

    return(FALSE);
}
