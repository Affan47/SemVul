_resv_overlap(time_t start_time, time_t end_time,
			  uint16_t flags, bitstr_t *node_bitmap,
			  slurmctld_resv_t *this_resv_ptr)
{
	ListIterator iter;
	slurmctld_resv_t *resv_ptr;
	bool rc = false;
	int i, j;
	time_t s_time1, s_time2, e_time1, e_time2;

	if ((flags & RESERVE_FLAG_MAINT)   ||
	    (flags & RESERVE_FLAG_OVERLAP) ||
	    (!node_bitmap))
		return rc;

	iter = list_iterator_create(resv_list);
	if (!iter)
		fatal("malloc: list_iterator_create");

	while ((resv_ptr = (slurmctld_resv_t *) list_next(iter))) {
		if (resv_ptr == this_resv_ptr)
			continue;
		if (resv_ptr->node_bitmap == NULL)
			continue;
		if (!bit_overlap(resv_ptr->node_bitmap, node_bitmap))
			continue;

		for (i=0; ((i<7) && (!rc)); i++) {
			s_time1 = start_time;
			e_time1 = end_time;
			_advance_time(&s_time1, i);
			_advance_time(&e_time1, i);
			for (j=0; ((j<7) && (!rc)); j++) {
				s_time2 = resv_ptr->start_time;
				e_time2 = resv_ptr->end_time;
				_advance_time(&s_time2, j);
				_advance_time(&e_time2, j);
				if ((s_time1 < e_time2) &&
				    (e_time1 > s_time2)) {
					verbose("Reservation overlap with %s",
						resv_ptr->name);
					rc = true;
					break;
				}
				if (!(resv_ptr->flags & RESERVE_FLAG_DAILY))
					break;
			}
			if ((flags & RESERVE_FLAG_DAILY) == 0)
				break;
		}
	}
	list_iterator_destroy(iter);

	return rc;
}
