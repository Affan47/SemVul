icalgauge_compare_recurse(icalcomponent* comp, icalcomponent* gauge)
{
    int pass = 1,localpass = 0;
    icalproperty *p;
    icalcomponent *child,*subgauge;
    icalcomponent_kind gaugekind, compkind;

    icalerror_check_arg_rz( (comp!=0), "comp");
    icalerror_check_arg_rz( (gauge!=0), "gauge");

    gaugekind = icalcomponent_isa(gauge);
    compkind = icalcomponent_isa(comp);

    if( ! (gaugekind == compkind || gaugekind == ICAL_ANY_COMPONENT) ){
	return 0;
    }


    for(p = icalcomponent_get_first_property(gauge,ICAL_ANY_PROPERTY);
	p != 0;
	p = icalcomponent_get_next_property(gauge,ICAL_ANY_PROPERTY)){

	icalproperty* targetprop;
	icalparameter* compareparam;
	icalparameter_xliccomparetype compare;
	int rel;


	compareparam = icalproperty_get_first_parameter(
	    p,
	    ICAL_XLICCOMPARETYPE_PARAMETER);

	if (compareparam!=0){
	    compare = icalparameter_get_xliccomparetype(compareparam);
	} else {
	    compare = ICAL_XLICCOMPARETYPE_EQUAL;
	}


	targetprop = icalcomponent_get_first_property(comp,
						      icalproperty_isa(p));

	if(targetprop != 0){


	    rel = icalvalue_compare(icalproperty_get_value(p),
				    icalproperty_get_value(targetprop));


	    if (rel == compare){
		localpass++;
	    } else if (compare == ICAL_XLICCOMPARETYPE_LESSEQUAL &&
		       ( rel == ICAL_XLICCOMPARETYPE_LESS ||
			 rel == ICAL_XLICCOMPARETYPE_EQUAL)) {
		localpass++;
	    } else if (compare == ICAL_XLICCOMPARETYPE_GREATEREQUAL &&
		       ( rel == ICAL_XLICCOMPARETYPE_GREATER ||
			 rel == ICAL_XLICCOMPARETYPE_EQUAL)) {
		localpass++;
	    } else if (compare == ICAL_XLICCOMPARETYPE_NOTEQUAL &&
		       ( rel == ICAL_XLICCOMPARETYPE_GREATER ||
			 rel == ICAL_XLICCOMPARETYPE_LESS)) {
		localpass++;
	    } else {
		localpass = 0;
	    }

	    pass = pass && (localpass>0);
	}
    }


    for(subgauge = icalcomponent_get_first_component(gauge,ICAL_ANY_COMPONENT);
	subgauge != 0;
	subgauge = icalcomponent_get_next_component(gauge,ICAL_ANY_COMPONENT)){

	gaugekind = icalcomponent_isa(subgauge);

	if (gaugekind == ICAL_ANY_COMPONENT){
	    child = icalcomponent_get_first_component(comp,ICAL_ANY_COMPONENT);
	} else {
	    child = icalcomponent_get_first_component(comp,gaugekind);
	}

	if(child !=0){
	    localpass = icalgauge_compare_recurse(child,subgauge);
	    pass = pass && localpass;
	} else {
	    pass = 0;
	}
    }

    return pass;
}
