journal_open(const char *fn, size_t fslimit, uint16_t bflags)
{

	if (fn == NULL) {
		return NULL;
	}

	journal_t *j = malloc(sizeof(journal_t));
	if (j == NULL) {
		return NULL;
	}

	memset(j, 0, sizeof(journal_t));
	j->bflags = bflags;
	j->fd = -1;


	if (fslimit == 0) {
		j->fslimit = FSLIMIT_INF;
	} else {
		j->fslimit = fslimit;
	}


	j->path = strdup(fn);
	if (j->path == NULL) {
		free(j);
		return NULL;
	}

	if (pthread_mutex_init(&j->mutex, NULL) != 0) {
		free(j->path);
		free(j);
		return NULL;
	}
	return j;
}
