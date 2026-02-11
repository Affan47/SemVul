reset_attr(int level)
{
	unsigned a = l_levels[level].attr;
	if(l_targets[l_levels[level].target].flags & LOG_ANSI)
	{
		if(!(a & ANSI_SUPPORTED_FLAGS))
			return;

		log_write_raw(l_levels[level].target, "\033[0m");
	}
	else if(l_targets[l_levels[level].target].flags & LOG_HTML)
	{
		if(a & LOG_BLINK)
			log_write_raw(l_levels[level].target, "</BLINK>");
		if(a & LOG_STRONG)
			log_write_raw(l_levels[level].target, "</STRONG>");
		if(a & LOG_COLORS)
			log_write_raw(l_levels[level].target, "</FONT>");
	}
}
