icalparameter_new_from_string(const char *str)
{
    char* eq;
    char* cpy;
    icalparameter_kind kind;
    icalparameter *param;

    icalerror_check_arg_rz(str != 0,"str");

    cpy = icalmemory_strdup(str);

    if (cpy == 0){
        icalerror_set_errno(ICAL_NEWFAILED_ERROR);
        return 0;
    }

    eq = strchr(cpy,'=');

    if(eq == 0){
        icalerror_set_errno(ICAL_MALFORMEDDATA_ERROR);
        return 0;
    }

    *eq = '\0';

    eq++;

    kind = icalparameter_string_to_kind(cpy);

    if(kind == ICAL_NO_PARAMETER){
        icalerror_set_errno(ICAL_MALFORMEDDATA_ERROR);
        return 0;
    }

    param = icalparameter_new_from_value_string(kind,eq);

    if(kind == ICAL_X_PARAMETER){
        icalparameter_set_xname(param,cpy);
    }

    free(cpy);

    return param;

}
