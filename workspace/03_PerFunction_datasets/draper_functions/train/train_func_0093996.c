task_complete(struct work_queue_task *t)
{
	checkpoint_task(t);

	if(t->result == 0) {
		debug(D_DEBUG, "task complete: %s: %s", t->tag, t->command_line);
		if(strlen(t->output) > 0) {
			char *out = strdup(t->output);
			char *cand1 = malloc(sizeof(char) * 500);
			char *cand2 = malloc(sizeof(char) * 500);
			int dir, start1, start2;
			char *line = strtok(out, "\n");
			int result = sscanf(line, "%s\t%s\t%d\t%d\t%d", cand1, cand2, &dir, &start1, &start2);
			while(result == 5) {
				cand_count++;
				line = strtok(NULL, "\n");
				if(line == NULL) {
					break;
				}
				result = sscanf(line, "%s\t%s\t%d\t%d\t%d", cand1, cand2, &dir, &start1, &start2);
			}
			free(out);
			free(cand1);
			free(cand2);
		}
		fputs(t->output, outfile);
		fflush(outfile);
		total_processed++;
		tasks_runtime += (t->time_receive_output_finish - t->time_send_input_start);
		tasks_filetime += t->total_transfer_time;
		work_queue_task_delete(t);
	} else {
		debug(D_DEBUG, "task failed: %s: %s", t->tag, t->command_line);

		if(retry_max > total_retried) {
			debug(D_DEBUG, "retrying task %d/%d", total_retried, retry_max);
			total_retried++;
			work_queue_submit(q, t);
		} else {
			fprintf(stderr, "%s: giving up after retrying %d tasks.\n", progname, retry_max);
			exit(1);
		}
	}
}
