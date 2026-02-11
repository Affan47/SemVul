header_option(void)
{
	if (PATTERN_is(JOB->current[0], RS_EXPORT))
	{
		JOB->current++;
		JOB->class->exported = TRUE;

		if (PATTERN_is(JOB->current[0], RS_OPTIONAL))
		{
			JOB->current++;
			JOB->class->optional = TRUE;
		}

		return TRUE;
	}

	if (PATTERN_is(JOB->current[0], RS_CREATE))
	{
		JOB->current++;

		if (PATTERN_is_newline(JOB->current[0]) || PATTERN_is(JOB->current[0], RS_STATIC))
		{
			JOB->class->autocreate = TRUE;
			if (PATTERN_is(JOB->current[0], RS_STATIC))
				JOB->current++;
			return TRUE;
		}
		else if (PATTERN_is(JOB->current[0], RS_PRIVATE))
		{
			JOB->class->nocreate = TRUE;
			JOB->current++;
			return TRUE;
		}
	}

	return FALSE;
}
