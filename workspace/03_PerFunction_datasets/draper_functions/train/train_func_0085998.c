jack_destroy_shm (jack_shm_info_t* si)
{

	if (si->index == JACK_SHM_NULL_INDEX)
		return;

	jack_remove_shm (&jack_shm_registry[si->index].id);
	jack_release_shm_info (si->index);
}
