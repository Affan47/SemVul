ftrace_destroy_event_types(void)
{
	int i, j;

	for (i = 0; i < nr_event_types; i++) {
		for (j = 0; j < event_types[i]->nfields; j++) {
			free(event_types[i]->fields[j].name);
			free(event_types[i]->fields[j].type);
		}

		free(event_types[i]->fields);
		free(event_types[i]->system);
		free(event_types[i]->name);
		free(event_types[i]->print_fmt);
		free(event_types[i]);
	}

	free(event_types);
	free(ftrace_common_fields);
}
