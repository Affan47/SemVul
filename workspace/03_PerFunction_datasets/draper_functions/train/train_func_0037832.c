time_to_update(struct execi_data *ed)
{
	if (!ed->interval)
		return 0;
	if (current_update_time - ed->last_update >= ed->interval)
		return 1;
	return 0;
}
