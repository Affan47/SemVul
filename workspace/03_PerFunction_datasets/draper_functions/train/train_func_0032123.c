still_should_show_file (NautilusView *view, NautilusFile *file, NautilusDirectory *directory)
{
	return nautilus_view_should_show_file (view, file) &&
		view_file_still_belongs (view, file, directory);
}
