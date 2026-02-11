fil_space_reserve_free_extents(

	ulint	id,
	ulint	n_free_now,
	ulint	n_to_reserve)
{
	fil_space_t*	space;
	ibool		success;

	ut_ad(fil_system);

	mutex_enter(&fil_system->mutex);

	space = fil_space_get_by_id(id);

	ut_a(space);

	if (space->n_reserved_extents + n_to_reserve > n_free_now) {
		success = FALSE;
	} else {
		space->n_reserved_extents += n_to_reserve;
		success = TRUE;
	}

	mutex_exit(&fil_system->mutex);

	return(success);
}
