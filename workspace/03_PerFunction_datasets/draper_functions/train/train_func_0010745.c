dessert_sysrxcb_del(dessert_sysrxcb_t* c) {
	int count = 0;
	dessert_sysrxcbe_t *i, *last;

	pthread_rwlock_wrlock(&dessert_cfglock);

	if (_dessert_sysrxcblist == NULL) {
		goto dessert_sysrxcb_del_out;
	}

	while (_dessert_sysrxcblist->c == c) {
		count++;
		i = _dessert_sysrxcblist;
		_dessert_sysrxcblist = _dessert_sysrxcblist->next;
		free(i);
		if (_dessert_sysrxcblist == NULL) {
			goto dessert_sysrxcb_del_out;
		}
	}

	for (i = _dessert_sysrxcblist; i->next != NULL; i = i->next) {
		if (i->c == c) {
			count++;
			last->next = i->next;
			free(i);
			i = last;
		}
		last = i;
	}

	dessert_sysrxcb_del_out: _dessert_sysrxcblistver++;
	pthread_rwlock_unlock(&dessert_cfglock);
	return ((count > 0) ? DESSERT_OK : DESSERT_ERR);

}
