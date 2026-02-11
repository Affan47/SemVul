_release_lock(const char *file, int unlock)
{
	struct lock_list *ll;
	struct dm_list *llh, *llt;

	dm_list_iterate_safe(llh, llt, &_lock_list) {
		ll = dm_list_item(llh, struct lock_list);

		if (!file || !strcmp(ll->res, file)) {
			dm_list_del(llh);
			if (unlock) {
				log_very_verbose("Unlocking %s", ll->res);
				if (flock(ll->lf, LOCK_NB | LOCK_UN))
					log_sys_error("flock", ll->res);
			}

			_undo_flock(ll->res, ll->lf);

			dm_free(ll->res);
			dm_free(llh);

			if (file)
				return 1;
		}
	}

	return 0;
}
