file_info_reparent_all(fileinfo_t *from, fileinfo_t *to)
{
	file_info_check(from);
	file_info_check(to);
	g_assert(0 == from->done);
	g_assert(0 != strcmp(from->pathname, to->pathname));

	file_info_unlink(from);
	download_info_change_all(from, to);


	g_assert(0 == from->refcount);
	g_assert(0 == from->lifecount);

	file_info_hash_remove(from);
	fi_free(from);
}
