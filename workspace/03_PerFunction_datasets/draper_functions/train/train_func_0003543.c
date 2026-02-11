wi_fsevents_remove_all_paths(wi_fsevents_t *fsevents) {
#ifdef _WI_FSEVENTS_ANY
	wi_enumerator_t		*enumerator;
	int					fd;

	enumerator = wi_dictionary_data_enumerator(fsevents->fds_for_paths);

	while((fd = (int) (intptr_t) wi_enumerator_next_data(enumerator))) {
#if defined(_WI_FSEVENTS_KQUEUE)
		close(fd);
#elif defined(_WI_FSEVENTS_INOTIFY)
		inotify_rm_watch(fsevents->inotify, fd);
#endif
	}

	wi_mutable_set_remove_all_data(fsevents->paths);
	wi_mutable_dictionary_remove_all_data(fsevents->fds_for_paths);

#ifdef _WI_FSEVENTS_INOTIFY
	wi_mutable_dictionary_remove_all_data(fsevents->paths_for_fds);
#endif
#endif
}
