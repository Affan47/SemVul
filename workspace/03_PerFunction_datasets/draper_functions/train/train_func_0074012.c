icalvalue_trigger_as_ical_string(icalvalue* value) {

    struct icaltriggertype data;

    icalerror_check_arg_rz( (value!=0),"value");
    data = icalvalue_get_trigger(value);

    if(!icaltime_is_null_time(data.time)){
	return icaltime_as_ical_string(data.time);
    } else {
	return icaldurationtype_as_ical_string(data.duration);
    }

}
