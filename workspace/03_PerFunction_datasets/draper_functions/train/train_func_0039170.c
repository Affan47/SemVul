work_queue_task_specify_directory(struct work_queue_task *t, const char *local_name, const char *remote_name, int type, int flags, int recursive) {
	struct list *files;
	struct work_queue_file *tf;

	if(!t || !remote_name) {
		return 0;
	}


	if(remote_name[0] == '/') {
		return 0;
	}

	if(type == WORK_QUEUE_OUTPUT || recursive) {
		return work_queue_task_specify_file(t, local_name, remote_name, type, flags);
	}

	files = t->input_files;

	list_first_item(files);
	while((tf = (struct work_queue_file*)list_next_item(files))) {
		if(!strcmp(remote_name, tf->remote_name))
		{	return 0;	}
	}

	tf = work_queue_file_create(remote_name, WORK_QUEUE_DIRECTORY, flags);
	list_push_tail(files, tf);
	return 1;

}
