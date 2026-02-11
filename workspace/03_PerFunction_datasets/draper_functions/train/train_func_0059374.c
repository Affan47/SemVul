setup_defaults(icalrecur_iterator* impl,
		    enum byrule byrule, icalrecurrencetype_frequency req,
		    int deftime, int *timepart)
{

    icalrecurrencetype_frequency freq;
    freq = impl->rule.freq;


    if(impl->by_ptrs[byrule][0] == ICAL_RECURRENCE_ARRAY_MAX &&
	expand_map[freq].map[byrule] != CONTRACT){
	impl->by_ptrs[byrule][0] = (short)deftime;
    }


    if( freq != req && expand_map[freq].map[byrule] != CONTRACT){
	*timepart = impl->by_ptrs[byrule][0];
    }


}
