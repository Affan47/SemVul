__acl_reorder_obj_p(acl_obj *acl_obj_p)
{
	acl_entry_obj **vector = alloca(sizeof(acl_entry_obj *) *
					acl_obj_p->aused), **v, *x;
	acl_entry_obj *entry_obj_p;

	if (acl_obj_p->aused <= 1)
		return 0;

	v = vector;
	FOREACH_ACL_ENTRY(entry_obj_p, acl_obj_p) {
		*v++ = entry_obj_p;
	}

	qsort(vector, acl_obj_p->aused, sizeof(acl_entry_obj *),
	       __acl_entry_pp_compare);

	x = (acl_entry_obj *)acl_obj_p;
	for (v = vector; v != vector + acl_obj_p->aused; v++) {
		(*v)->eprev = x;
		x = *v;
	}
	acl_obj_p->aprev = *(vector + acl_obj_p->aused - 1);

	x = (acl_entry_obj *)acl_obj_p;
	for (v = vector + acl_obj_p->aused - 1; v != vector - 1; v--) {
		(*v)->enext = x;
		x = *v;
	}
	acl_obj_p->anext = *vector;
	return 0;
}
