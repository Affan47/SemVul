nodetrack_new(nodetrack_callback_t callback, gpointer user_data)
{
	nodetrack_t*	ret = MALLOCT(nodetrack_t);
	if (!mbr_inityet) {
		init_global_membership();
	}
	if (!ret) {
		return ret;
	}
	nodetrack_t_count++;
	ret->refcount = 0;
	if (!create_new_hashtables(&ret->nt))  {
		free(ret);
		ret = NULL;
	}
	ret->user_data = user_data;
	ret->callback = callback;
	ret->extra_callback = NULL;
	ret->ext_data = NULL;
	return ret;
}
