check_contract_restriction(icalrecur_iterator* impl,
		      enum byrule byrule, int v)
{
    int pass = 0;
    int itr;
    icalrecurrencetype_frequency freq = impl->rule.freq;

    if(impl->by_ptrs[byrule][0]!=ICAL_RECURRENCE_ARRAY_MAX &&
	expand_map[freq].map[byrule] == CONTRACT){
	for(itr=0; impl->by_ptrs[byrule][itr]!=ICAL_RECURRENCE_ARRAY_MAX;itr++){
	    if(impl->by_ptrs[byrule][itr] == v){
		pass=1;
		break;
	    }
	}

	return pass;
    } else {


	return 1;
    }
}
