stat_seq_start(struct seq_file *s, loff_t *pos)
{
	struct stat_session *session = s->private;
	struct rb_node *node;
	int n = *pos;
	int i;


	mutex_lock(&session->stat_mutex);


	if (session->ts->stat_headers) {
		if (n == 0)
			return SEQ_START_TOKEN;
		n--;
	}

	node = rb_first(&session->stat_root);
	for (i = 0; node && i < n; i++)
		node = rb_next(node);

	return node;
}
