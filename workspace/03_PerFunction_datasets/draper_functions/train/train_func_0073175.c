brief_tooltip_handler(char *str)
{
	if (!stricmp(str, NOX("@close"))) {
		if (Closeup_icon)
			return XSTR( "Close", 428);
	}

	return NULL;
}
