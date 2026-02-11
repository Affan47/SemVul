strace_read_unfinished(char * line, hash_table_t * ht) {
	isyscall_t * isyscall;
	item_t * item;
	int pid;

	sscanf(line, "%d", &pid);

	if ( (item = hash_table_find(ht, &pid)) == NULL) {
		isyscall = malloc(sizeof(isyscall_t));
		item_init(&isyscall->item);
		strncpy(isyscall->line, line, MAX_STRING);
		isyscall->pid = pid;
		hash_table_insert(ht, &pid, &isyscall->item);

	} else {
		isyscall = hash_table_entry(item, isyscall_t, item);
		ERRORPRINTF("Already have unfinished syscall for pid: %d. %s", pid, isyscall->line);
	}
}
