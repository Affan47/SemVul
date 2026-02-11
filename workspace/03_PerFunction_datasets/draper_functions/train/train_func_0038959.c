match_proc(void *data, Objid oid)
{
    struct match_data *d = data;
    Var *names = aliases(oid);
    int i;
    const char *name;

    for (i = 0; i <= names[0].v.num; i++) {
	if (i == 0)
	    name = db_object_name(oid);
	else if (names[i].type != TYPE_STR)
	    continue;
	else
	    name = names[i].v.str;

	if (!mystrncasecmp(name, d->name, d->lname)) {
	    if (name[d->lname] == '\0') {
		if (d->exact == NOTHING || d->exact == oid)
		    d->exact = oid;
		else
		    return 1;
	    } else {
		if (d->partial == FAILED_MATCH || d->partial == oid)
		    d->partial = oid;
		else
		    d->partial = AMBIGUOUS;
	    }
	}
    }

    return 0;
}
