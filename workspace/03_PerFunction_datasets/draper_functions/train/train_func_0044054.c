db_add_verb(Objid oid, const char *vnames, Objid owner, unsigned flags,
	    db_arg_spec dobj, db_prep_spec prep, db_arg_spec iobj)
{
    Object *o = dbpriv_find_object(oid);
    Verbdef *v, *newv;
    int count;

    db_priv_affected_callable_verb_lookup();

    newv = mymalloc(sizeof(Verbdef), M_VERBDEF);
    newv->name = vnames;
    newv->owner = owner;
    newv->perms = flags | (dobj << DOBJSHIFT) | (iobj << IOBJSHIFT);
    newv->prep = prep;
    newv->next = 0;
    newv->program = 0;
    if (o->verbdefs) {
	for (v = o->verbdefs, count = 2; v->next; v = v->next, ++count);
	v->next = newv;
    } else {
	o->verbdefs = newv;
	count = 1;
    }
    return count;
}
