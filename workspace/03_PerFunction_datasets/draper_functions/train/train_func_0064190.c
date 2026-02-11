shared_file_remove(shared_file_t *sf)
{
	shared_file_check(sf);

	shared_file_deindex(sf);
	if (0 == sf->refcnt) {
		shared_file_free(&sf);
	}
}
