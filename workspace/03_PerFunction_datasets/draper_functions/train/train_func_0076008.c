NK6510_GetToDo(gn_data *data, struct gn_statemachine *state)
{
	gn_error error;

	if (DRVINSTANCE(state)->pm->flags & PM_EXTCALENDAR)
		return NK6510_GetToDo_S40_30(data, state);

	if (data->todo->location < 1) {
		error = GN_ERR_INVALIDLOCATION;
	} else {
		error = NK6510_GetToDoLocations(data, state);
		if (error == GN_ERR_NONE) {
			if (!data->todo_list->number ||
			    data->todo->location > data->todo_list->number) {
				error = GN_ERR_EMPTYLOCATION;
			} else {
				return NK6510_GetToDo_Internal(data, state, data->todo_list->location[data->todo->location - 1]);
			}
		}
	}
	return error;
}
