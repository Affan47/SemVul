icalproperty_set_recurrenceid(icalproperty* prop, struct icaltimetype v){
    icalvalue *value;

    icalerror_check_arg_rv( (prop!=0),"prop");
    value = icalvalue_new_datetime(v);
    icalproperty_set_value(prop,value);
}
