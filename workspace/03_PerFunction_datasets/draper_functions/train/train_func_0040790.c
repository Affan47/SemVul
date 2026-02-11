icalcomponent_set_dtstart(icalcomponent* comp, struct icaltimetype v)
{

    icalcomponent *inner = icalcomponent_get_inner(comp);
    icalproperty *prop
	= icalcomponent_get_first_property(inner, ICAL_DTSTART_PROPERTY);


    if (prop == 0){
	prop = icalproperty_new_dtstart(v);
	icalcomponent_add_property(inner, prop);
    }

    icalproperty_set_dtstart(prop,v);

}
