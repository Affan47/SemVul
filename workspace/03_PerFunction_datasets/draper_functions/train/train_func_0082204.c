ssyacc_add_where(struct icalgauge_impl* impl, char* str1,
	icalgaugecompare compare , char* value_str)
{

    struct icalgauge_where *where;
    char *compstr, *propstr, *c, *s,*l;

    if ( (where = malloc(sizeof(struct icalgauge_where))) ==0){
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return;
    }

    memset(where,0,sizeof(struct icalgauge_where));
    where->logic = ICALGAUGELOGIC_NONE;
    where->compare = ICALGAUGECOMPARE_NONE;
    where->comp = ICAL_NO_COMPONENT;
    where->prop = ICAL_NO_PROPERTY;


    s = value_str;
    if(*s == '\''){
	s++;
    }
    l = s+strlen(s)-1;
    if(*l == '\''){
	*l=0;
    }

    where->value = strdup(s);


    if( (c = strrchr(str1,'.')) != 0){
	compstr = str1;
	propstr = c+1;
	*c = '\0';
    } else {
	compstr = 0;
	propstr = str1;
    }


    if(compstr != 0){
	where->comp = icalenum_string_to_component_kind(compstr);
    } else {
	where->comp = ICAL_NO_COMPONENT;
    }

    where->prop = icalenum_string_to_property_kind(propstr);

    where->compare = compare;

    if(where->value == 0){
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	free(where->value);
	return;
    }

    pvl_push(impl->where,where);
}
