icalvalue_get_x(icalvalue* value) {

    icalerror_check_arg_rz( (value!=0),"value");
    icalerror_check_value_type(value, ICAL_X_VALUE);
    return ((struct icalvalue_impl*)value)->x_value;
}
