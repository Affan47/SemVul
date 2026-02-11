icaltimezone_expand_changes		(icaltimezone *zone,
					 int		 end_year)
{
    icalarray *changes;
    icalcomponent *comp;

#if 0
    printf ("\nExpanding changes for: %s to year: %i\n", zone->tzid, end_year);
#endif

    changes = icalarray_new (sizeof (icaltimezonechange), 32);
    if (!changes)
	return;


    comp = icalcomponent_get_first_component (zone->component,
					      ICAL_ANY_COMPONENT);
    while (comp) {
	icaltimezone_expand_vtimezone (comp, end_year, changes);
	comp = icalcomponent_get_next_component (zone->component,
						 ICAL_ANY_COMPONENT);
    }


    icalarray_sort (changes, icaltimezone_compare_change_fn);

    if (zone->changes)
	icalarray_free (zone->changes);

    zone->changes = changes;
    zone->end_year = end_year;
}
