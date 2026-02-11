choose_a_rule(int rflags)
{
    char      *choice = NULL;
    char     **rule_list, **lp;
    int        cnt = 0;
    PAT_S     *pat;
    PAT_STATE  pstate;

    if(!(nonempty_patterns(rflags, &pstate) && first_pattern(&pstate))){
	q_status_message(SM_ORDER, 3, 3,
			 _("No rules available. Use Setup/Rules to add some."));
	return(choice);
    }


    for(pat = first_pattern(&pstate); pat; pat = next_pattern(&pstate))
      cnt++;

    if(cnt <= 0){
	q_status_message(SM_ORDER, 3, 4, _("No rules defined, use Setup/Rules"));
	return(choice);
    }

    lp = rule_list = (char **) fs_get((cnt + 1) * sizeof(*rule_list));
    memset(rule_list, 0, (cnt+1) * sizeof(*rule_list));

    for(pat = first_pattern(&pstate); pat; pat = next_pattern(&pstate))
      *lp++ = cpystr((pat->patgrp && pat->patgrp->nick)
			  ? pat->patgrp->nick : "?");


    choice = choose_item_from_list(rule_list, NULL, _("SELECT A RULE"),
				   _("rules"), h_select_rule_screen,
				   _("HELP FOR SELECTING A RULE NICKNAME"), NULL);

    if(!choice)
      q_status_message(SM_ORDER, 1, 4, "No choice");

    free_list_array(&rule_list);

    return(choice);
}
