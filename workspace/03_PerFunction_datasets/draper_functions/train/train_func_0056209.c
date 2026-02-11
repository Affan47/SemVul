replace_master (ECalBackendCalDAV *cbdav,
                icalcomponent *old_comp,
                icalcomponent *new_master)
{
	icalcomponent *old_master;
	if (icalcomponent_isa (old_comp) != ICAL_VCALENDAR_COMPONENT) {
		icalcomponent_free (old_comp);
		return new_master;
	}

	old_master = get_master_comp (cbdav, old_comp);
	if (!old_master) {

		icalcomponent_free (new_master);
	} else {
		icalcomponent_remove_component (old_comp, old_master);
		icalcomponent_free (old_master);

		icalcomponent_add_component (old_comp, new_master);
	}

	return old_comp;
}
