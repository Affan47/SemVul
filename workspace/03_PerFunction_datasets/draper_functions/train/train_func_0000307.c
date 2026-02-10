log(const c8* message, const c8* hint, ELOG_LEVEL ll)
	{
		if (Logger)
			Logger->log(message, hint, ll);
	}
