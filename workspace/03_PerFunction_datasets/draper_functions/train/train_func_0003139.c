icalfileset_select(icalset* set, icalgauge* gauge)
{
    icalfileset *fset = (icalfileset*) set;

    icalerror_check_arg_re(gauge!=0,"gauge",ICAL_BADARG_ERROR);

    fset->gauge = gauge;

    return ICAL_NO_ERROR;
}
