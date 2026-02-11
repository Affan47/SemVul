del_queue(char *name)
{
	struct ast_queue *prev = NULL, *queue = queues;
	struct ast_queuename *qn;
	while(queue) {
		if (!strcmp(name, queue->name)) {
			qn = find_queuename(queue->queue);
			if (qn) {
				qn->current--;
				gui_queue_set_queueinfo(qn->obj, qn->current, qn->max);
			}
			if (currentq == queue)
				currentq = NULL;
			if (prev)
				prev->next = queue->next;
			else
				queues = queue->next;
			gui_del_queue(queue->obj);
			queue->magic = 0;
			free(queue);
			return;
		}
		prev = queue;
		queue = queue->next;
	}

}
