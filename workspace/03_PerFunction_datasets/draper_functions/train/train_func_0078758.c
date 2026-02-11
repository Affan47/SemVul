get_workload_specs(const char *path) {

	struct list *specs = list_create();
	if(!specs) {
		fprintf(stderr, "Cannot allocate memory for creating list!\n");
		return NULL;
	}


	FILE *fp;

	fp = fopen(path, "r");
	if(!fp) {
		fprintf(stderr, "Failed to open workload specification file at %s.\n", path);
		return NULL;
	}

	char *line;
	int line_count = 0;
	while((line = get_line(fp))) {
		line_count++;

		string_chomp(line);
		if(string_isspace(line)) {
			continue;
		}
		if(line[0] == '#') {
			continue;
		}

		int submit, input, exe, output, num;
		if(sscanf(line, "%d %d %d %d %d", &submit, &input, &exe, &output, &num) == 5) {
			if(submit < 0 || input <=0 || exe <=0 || output <=0 || num <=0) {
				fprintf(stderr, "Other than the submit_time field, every other field should be greater than 0.\n");
				goto fail;
			}

			struct task_series *ts = (struct task_series *)xxmalloc(sizeof(struct task_series));
			ts->submit_time = submit;
			ts->input_size = input;
			ts->execution_time = exe;
			ts->output_size = output;
			ts->num_of_tasks = num;

			list_push_priority(specs, ts, ts->submit_time);
		} else {
			fprintf(stderr, "Line %d is invalid: %s\n", line_count, line);
			goto fail;
		}
	}
	fclose(fp);
	return specs;

fail:

	list_free(specs);
	list_delete(specs);
	fclose(fp);
	return NULL;
}
