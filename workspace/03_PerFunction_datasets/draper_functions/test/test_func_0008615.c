db_find_command_verb(Objid oid, const char *verb,
		     db_arg_spec dobj, unsigned prep, db_arg_spec iobj)
{
    Object *o;
    Verbdef *v;
    static handle h;
    db_verb_handle vh;

    Var ancestors;
    Var ancestor;
    int i, c;

    ancestors = db_ancestors(oid, false);
    ancestors = listinsert(ancestors, new_obj(oid), 1);

    FOR_EACH(ancestor, ancestors, i, c) {
	o = dbpriv_find_object(ancestor.v.obj);
	for (v = o->verbdefs; v; v = v->next) {
	    db_arg_spec vdobj = (v->perms >> DOBJSHIFT) & OBJMASK;
	    db_arg_spec viobj = (v->perms >> IOBJSHIFT) & OBJMASK;

	    if (verbcasecmp(v->name, verb)
		&& (vdobj == ASPEC_ANY || vdobj == dobj)
		&& (v->prep == PREP_ANY || v->prep == prep)
		&& (viobj == ASPEC_ANY || viobj == iobj)) {
		h.definer = o->id;
		h.verbdef = v;
		vh.ptr = &h;

		free_var(ancestors);

		return vh;
	    }
	}
    }

    free_var(ancestors);

    vh.ptr = 0;

    return vh;
}
