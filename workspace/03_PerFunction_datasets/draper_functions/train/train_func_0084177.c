utc_datetime_prop(int icaltype, VObject *object, icalcomponent *comp,
			icalvcal_defaults *defaults)
{
    icalproperty_kind kind = (icalproperty_kind)icaltype;
    icalproperty *prop;
    icalvalue *value;
    icalvalue_kind value_kind;
    char *s;
    int free_string;
    struct icaltimetype itt;

    prop = icalproperty_new(kind);

    value_kind = icalenum_property_kind_to_value_kind (icalproperty_isa(prop));

    s = get_string_value (object, &free_string);


    itt = icaltime_from_string (s);


    if (!itt.is_utc)
      convert_floating_time_to_utc (&itt);

    value = icalvalue_new_datetime (itt);
    icalproperty_set_value(prop,value);

    if (free_string)
	deleteStr (s);

    return (void*)prop;
}
