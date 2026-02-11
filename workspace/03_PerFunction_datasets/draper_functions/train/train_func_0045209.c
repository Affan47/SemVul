ab_whereis(int *warped, int command_line)
{
    int rc, wrapped = 0;
    long new_top_ent, new_line;

    dprint((5, "- ab_whereis -\n"));

    rc = search_book(as.top_ent+as.cur_row, command_line,
		    &new_line, &wrapped, warped);

    new_top_ent = NO_LINE;

    if(rc == -2)
      q_status_message(SM_INFO, 0, 2, _("Address book search cancelled"));

    else if(rc == -1)
      q_status_message(SM_ORDER, 0, 4, _("Word not found"));

    else if(rc == 0){

	if(wrapped == 1)
	  q_status_message(SM_INFO, 0, 2, _("Search wrapped to beginning"));
	else if(wrapped == 2)
	  q_status_message(SM_INFO, 0, 2,
			   _("Current line contains the only match"));


	if(!*warped &&
	    new_line >= as.top_ent &&
	    new_line < as.top_ent+as.l_p_page)
	    new_top_ent = as.top_ent;

	else
	  new_top_ent = first_line(new_line - as.l_p_page/2);

	as.cur_row  = new_line - new_top_ent;
    }

    return(new_top_ent);
}
