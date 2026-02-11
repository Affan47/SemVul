prepare_update_file(struct view *view, const char *name)
{
	if (view->pipe)
		end_update(view, TRUE);
	return io_open(&view->io, "%s", name);
}
