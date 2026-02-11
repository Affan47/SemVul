PrintBooks(bookkeeper_t *bookkeeper) {
bookkeeper_list_t	*bookkeeper_list_entry;
struct tm *ts;
time_t	t;
char	string[32];

	if ( !bookkeeper ) {
		printf("No bookkeeper record available!\n");
		return;
	}

	bookkeeper_list_entry = Get_bookkeeper_list_entry(bookkeeper);
	if ( !bookkeeper_list_entry ) {

		LogError("Software error in %s line %d: %s", __FILE__, __LINE__, "Entry not found in list");
		return;
	}

	sem_lock(bookkeeper_list_entry->sem_id);
	printf("Collector process: %lu\n", (unsigned long)bookkeeper->nfcapd_pid);
	if ( bookkeeper->launcher_pid )
		printf("Launcher process: %lu\n", (unsigned long)bookkeeper->launcher_pid);
	else
		printf("Launcher process: <none>\n");
	printf("Record sequence : %llu\n", (unsigned long long)bookkeeper->sequence);

	t = bookkeeper->first;
    ts = localtime(&t);
    strftime(string, 31, "%Y-%m-%d %H:%M:%S", ts);
	string[31] = '\0';
	printf("First           : %s\n", bookkeeper->first ? string : "<not set>");

	t = bookkeeper->last;
    ts = localtime(&t);
    strftime(string, 31, "%Y-%m-%d %H:%M:%S", ts);
	string[31] = '\0';
	printf("Last            : %s\n", bookkeeper->last ? string : "<not set>");
	printf("Number of files : %llu\n", (unsigned long long)bookkeeper->numfiles);
	printf("Total file size : %llu\n", (unsigned long long)bookkeeper->filesize);
	printf("Max file size   : %llu\n", (unsigned long long)bookkeeper->max_filesize);
	printf("Max life time   : %llu\n", (unsigned long long)bookkeeper->max_lifetime);
	sem_unlock(bookkeeper_list_entry->sem_id);

}
