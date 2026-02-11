icalvalue_new_impl(icalvalue_kind kind){

    struct icalvalue_impl* v;

    if (!icalvalue_kind_is_valid(kind))
      return NULL;

    if ( ( v = (struct icalvalue_impl*)
	   malloc(sizeof(struct icalvalue_impl))) == 0) {
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return 0;
    }

    strcpy(v->id,"val");

    v->kind = kind;
    v->size = 0;
    v->parent = 0;
    v->x_value = 0;
    memset(&(v->data),0,sizeof(v->data));

    return v;

}
