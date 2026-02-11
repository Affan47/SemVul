add_work(enum work_type type, char *name, void *id)
{
	grep_lock();

	while ((todo_end+1) % ARRAY_SIZE(todo) == todo_done) {
		pthread_cond_wait(&cond_write, &grep_mutex);
	}

	todo[todo_end].type = type;
	todo[todo_end].name = name;
	todo[todo_end].identifier = id;
	todo[todo_end].done = 0;
	strbuf_reset(&todo[todo_end].out);
	todo_end = (todo_end + 1) % ARRAY_SIZE(todo);

	pthread_cond_signal(&cond_add);
	grep_unlock();
}
