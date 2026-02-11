quote_fmt_get_buffer(void)
{
	if (current != &main_expr)
		g_warning("Error: parser still in sub-expr mode\n");

	if (error != 0)
		return NULL;
	else
		return current->buffer;
}
