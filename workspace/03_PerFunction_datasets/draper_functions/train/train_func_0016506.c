waif_property_allows(Waif *w, db_prop_handle h, Objid progr, db_prop_flag flag)
{
	int flags = db_property_flags(h);

	return (flags & flag) ||
	    ((flags & PF_CHOWN) ? w->owner : db_property_owner(h)) == progr ||
	    is_wizard(progr);
}
