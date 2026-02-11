update_live_range (MonoMethodVar *var, int abs_pos)
{
	if (var->range.first_use.abs_pos > abs_pos)
		var->range.first_use.abs_pos = abs_pos;

	if (var->range.last_use.abs_pos < abs_pos)
		var->range.last_use.abs_pos = abs_pos;
}
