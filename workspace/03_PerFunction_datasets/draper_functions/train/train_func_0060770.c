gettodo(int argc, char *argv[], gn_data *data, struct gn_statemachine *state)
{
	gn_todo_list	todolist;
	gn_todo		todo;
	gn_error	error = GN_ERR_NONE;
	bool		vcal = false;
	int		i, first_location, last_location;

	struct option options[] = {
		{ "vCal",    optional_argument, NULL, 'v'},
		{ NULL,      0,                 NULL, 0}
	};

	first_location = gnokii_atoi(optarg);
	if (errno || first_location < 0)
		return gettodo_usage(stderr, -1);
	last_location = parse_end_value_option(argc, argv, optind, first_location);
	if (errno || last_location < 0)
		return gettodo_usage(stderr, -1);

	while ((i = getopt_long(argc, argv, "v", options, NULL)) != -1) {
		switch (i) {
		case 'v':
			vcal = true;
			break;
		default:
			return gettodo_usage(stderr, -1);
		}
	}

	for (i = first_location; i <= last_location; i++) {
		todo.location = i;

		gn_data_clear(data);
		data->todo = &todo;
		data->todo_list = &todolist;

		error = gn_sm_functions(GN_OP_GetToDo, data, state);
		switch (error) {
		case GN_ERR_NONE:
			if (vcal) {
				gn_todo2ical(stdout, &todo);
			} else {
				fprintf(stdout, _("%s: %s\n"), _("Todo"), todo.text);
				fprintf(stdout, _("%s: %s\n"), _("Priority"), gn_todo_priority2str(todo.priority));
			}
			break;
		default:

			if (last_location == INT_MAX) {

				if ((i > first_location) && ((error == GN_ERR_EMPTYLOCATION) || (error == GN_ERR_INVALIDLOCATION))) {
					error = GN_ERR_NONE;
				}
				last_location = 0;
			}
			if (error != GN_ERR_NONE) {
				fprintf(stderr, _("The ToDo note could not be read: %s\n"), gn_error_print(error));
			}
		}
	}
	return error;
}
