copy_file(const std::string & from_path, const std::string & to_path)
{
	if (!Glib::file_test (from_path, Glib::FILE_TEST_EXISTS)) return false;

	Glib::RefPtr<Gio::File> from_file = Gio::File::create_for_path(from_path);
	Glib::RefPtr<Gio::File> to_file = Gio::File::create_for_path(to_path);

	try
	{
		from_file->copy (to_file, Gio::FILE_COPY_OVERWRITE);
	}
	catch(const Glib::Exception& ex)
	{
		error << string_compose (_("Unable to Copy file %1 to %2 (%3)"),
				from_path, to_path, ex.what())
			<< endmsg;
		return false;
	}
	return true;
}
