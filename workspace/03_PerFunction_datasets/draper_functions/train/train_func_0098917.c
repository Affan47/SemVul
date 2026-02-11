add_to_process(struct process *process, struct latency_line *line)
{
	GList *item;
	struct latency_line *line2;
	item = g_list_first(process->latencies);
	while (item) {
		line2 = item->data;
		item = g_list_next(item);
		if (strcmp(line->reason, line2->reason)==0) {
			line2->count += line->count;
			line2->time += line->time;
			if (line->max > line2->max)
				line2->max = line->max;
			free(line);
			return;
		}
	}
	process->latencies = g_list_append(process->latencies, line);
}
