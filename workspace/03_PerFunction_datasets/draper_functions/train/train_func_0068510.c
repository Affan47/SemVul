warning_destination (cb_tree x)
{
	struct cb_reference	*r;
	struct cb_field		*f;
	cb_tree			loc;

	r = CB_REFERENCE (x);
	f = CB_FIELD (r->value);
	loc = CB_TREE (f);

	if (r->offset) {
		return;
	}

	if (!strcmp (f->name, "RETURN-CODE") ||
	    !strcmp (f->name, "SORT-RETURN") ||
	    !strcmp (f->name, "NUMBER-OF-CALL-PARAMETERS")) {
		cb_warning (_("Internal register '%s' defined as BINARY-LONG"), f->name);
	} else if (f->pic) {
		cb_warning_x (loc, _("'%s' defined here as PIC %s"), f->name, f->pic->orig);
	} else {
		cb_warning_x (loc, _("'%s' defined here as a group of length %d"), f->name, f->size);
	}
}
