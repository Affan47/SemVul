umethod_bind(VALUE method, VALUE recv)
{
    struct METHOD *data, *bound;

    TypedData_Get_Struct(method, struct METHOD, &method_data_type, data);

    if (data->rclass != CLASS_OF(recv) && !rb_obj_is_kind_of(recv, data->rclass)) {
	if (FL_TEST(data->rclass, FL_SINGLETON)) {
	    rb_raise(rb_eTypeError,
		     "singleton method called for a different object");
	}
	else {
	    rb_raise(rb_eTypeError, "bind argument must be an instance of %s",
		     rb_class2name(data->rclass));
	}
    }

    method = TypedData_Make_Struct(rb_cMethod, struct METHOD, &method_data_type, bound);
    *bound = *data;
    bound->me = ALLOC(rb_method_entry_t);
    *bound->me = *data->me;
    if (bound->me->def) bound->me->def->alias_count++;
    bound->recv = recv;
    bound->rclass = CLASS_OF(recv);
    data->ume = ALLOC(struct unlinked_method_entry_list_entry);

    return method;
}
