AccessBookkeeper(bookkeeper_t **bookkeeper, char *path) {
bookkeeper_list_t	**bookkeeper_list_entry;
int sem_key, shm_key, shm_id, sem_id;

	*bookkeeper = NULL;

	shm_key = _ftok(path, 1);
	if ( shm_key == - 1 )
		return ERR_PATHACCESS;


	shm_id = shmget(shm_key, sizeof(bookkeeper_t), 0600);

	if ( shm_id < 0 ) {


		switch (errno) {
			case ENOENT:

				return ERR_NOTEXISTS;
				break;
			case EACCES:


				LogError("Access denied to collector bookkeeping record.");
				return ERR_FAILED;
				break;
			default:

				LogError("semop() error in %s line %d: %s", __FILE__, __LINE__, strerror(errno) );
				return ERR_FAILED;
		}

	}


	sem_key = _ftok(path, 2);

	if ( sem_key == - 1 ) {

		return ERR_FAILED;
	}


	sem_id = semget(sem_key, 1, 0600);
	if ( sem_id == - 1 ) {

		LogError("semget() error in %s line %d: %s", __FILE__, __LINE__, strerror(errno) );

		return ERR_FAILED;
	}


	*bookkeeper = (bookkeeper_t *)shmat(shm_id, NULL, 0);
	if ( *bookkeeper == (bookkeeper_t *)-1 ) {
		LogError("shmat() error in %s line %d: %s", __FILE__, __LINE__, strerror(errno) );
		return ERR_FAILED;
	}

	bookkeeper_list_entry = &bookkeeper_list;
	while ( *bookkeeper_list_entry != NULL && (*bookkeeper_list_entry)->bookkeeper != NULL )
		bookkeeper_list_entry = &((*bookkeeper_list_entry)->next);


	if ( *bookkeeper_list_entry == NULL ) {
		(*bookkeeper_list_entry) = (bookkeeper_list_t *)malloc(sizeof(bookkeeper_list_t));
		if ( !*bookkeeper_list_entry ) {
			LogError("malloc() error in %s line %d: %s", __FILE__, __LINE__, strerror(errno) );
			return ERR_FAILED;
		}
		memset((void *)*bookkeeper_list_entry, 0, sizeof(bookkeeper_list_t));
	}

	(*bookkeeper_list_entry)->shm_id = shm_id;
	(*bookkeeper_list_entry)->sem_id = sem_id;
	(*bookkeeper_list_entry)->bookkeeper = *bookkeeper;
	(*bookkeeper_list_entry)->next = NULL;

	return BOOKKEEPER_OK;


}
