icaltriggertype_from_string(const char* str)
{


    struct icaltriggertype tr, null_tr;
    int old_ieaf = icalerror_errors_are_fatal;

    tr.time= icaltime_null_time();
    tr.duration = icaldurationtype_from_int(0);

    null_tr = tr;

    if(str == 0) goto error;


    icalerror_errors_are_fatal = 0;

    tr.time = icaltime_from_string(str);

    icalerror_errors_are_fatal = old_ieaf;

    if (icaltime_is_null_time(tr.time)){

	tr.duration = icaldurationtype_from_string(str);

	if(icaldurationtype_as_int(tr.duration) == 0) goto error;
    }

    return tr;

 error:
    icalerror_set_errno(ICAL_MALFORMEDDATA_ERROR);
    return null_tr;

}
