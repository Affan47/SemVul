add_newline()
{
	int action = PREP_CONTINUE;

	if (_prep)
	{
		int line = comp->line;

		add_pattern_no_dump(RT_NEWLINE, comp->line);
		action = PREP_analyze(&comp->pattern[_prep_index]);
		_prep = FALSE;

		comp->pattern_count = _prep_index;
		comp->line = line;
	}

	if (action == PREP_LINE)
		comp->line = PREP_next_line;

	add_pattern(RT_NEWLINE, comp->line);
	comp->line++;

	if (action == PREP_IGNORE)
		jump_to_next_prep();
}
