icalcomponent_count_components (icalcomponent* component,
				icalcomponent_kind kind)
{
    int count=0;
    pvl_elem itr;

    icalerror_check_arg_rz( (component!=0), "component");

    for( itr = pvl_head(component->components);
	 itr != 0;
	 itr = pvl_next(itr))
    {
	if(kind == icalcomponent_isa((icalcomponent*)pvl_data(itr)) ||
	    kind == ICAL_ANY_COMPONENT){
	    count++;
	}
    }

    return count;
}
