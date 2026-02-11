ba_create_geo_table(ba_geo_system_t *my_geo_system,
				bool avoid_three)
{
	ba_geo_table_t *geo_ptr;
	int dim, inx[my_geo_system->dim_count], passthru, product;
	struct ba_geo_table **last_pptr;

	if (my_geo_system->geo_table_ptr)
		return;

	xassert(my_geo_system->dim_count);
	my_geo_system->total_size = 1;
	for (dim = 0; dim < my_geo_system->dim_count; dim++) {
		if (my_geo_system->dim_size[dim] < 1)
			fatal("dim_size[%d]= %d", dim,
			      my_geo_system->dim_size[dim]);
		my_geo_system->total_size *= my_geo_system->dim_size[dim];
		inx[dim] = 1;
	}

	my_geo_system->geo_table_ptr = xmalloc(sizeof(ba_geo_table_t *) *
					       (my_geo_system->total_size+1));

	do {
		bool found_three = 0;

		geo_ptr = xmalloc(sizeof(ba_geo_table_t));
		geo_ptr->geometry = xmalloc(sizeof(uint16_t) *
					    my_geo_system->dim_count);
		product = 1;
		for (dim = 0; dim < my_geo_system->dim_count; dim++) {
			if (avoid_three && (inx[dim] == 3)) {
				found_three = 1;
				goto next_geo;
			}
			geo_ptr->geometry[dim] = inx[dim];
			product *= inx[dim];
			passthru = my_geo_system->dim_size[dim] - inx[dim];
			if (passthru == 0)
				geo_ptr->full_dim_cnt++;
			else if ((passthru > 1) && (inx[dim] > 1))
				geo_ptr->passthru_cnt += passthru;
		}
		geo_ptr->size = product;
		xassert(product <= my_geo_system->total_size);
		my_geo_system->geo_table_size++;


		last_pptr = &my_geo_system->geo_table_ptr[product];
		while (*last_pptr) {
			if (geo_ptr->full_dim_cnt > (*last_pptr)->full_dim_cnt)
				break;
			if ((geo_ptr->full_dim_cnt ==
			     (*last_pptr)->full_dim_cnt) &&
			    (geo_ptr->passthru_cnt <
			     (*last_pptr)->passthru_cnt))
				break;
			last_pptr = &((*last_pptr)->next_ptr);
		}
		geo_ptr->next_ptr = *last_pptr;
		*last_pptr = geo_ptr;
	next_geo:
		if (found_three) {
			xfree(geo_ptr->geometry);
			xfree(geo_ptr);
		}
	} while (_incr_geo(inx, my_geo_system));
}
