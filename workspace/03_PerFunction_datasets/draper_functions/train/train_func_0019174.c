icalvalue_time_as_ical_string(icalvalue* value) {

    struct icaltimetype data;
    char* str;
    icalerror_check_arg_rz( (value!=0),"value");
    data = icalvalue_get_time(value);

    str = (char*)icalmemory_tmp_buffer(8);

    str[0] = 0;
    print_time_to_string(str,&data);

    return str;
}
