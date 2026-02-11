report_build_and_save(const FoundSet& found_set, const sharedptr<const Report>& report)
{
  const Glib::ustring contents = report_build(found_set, report);


  const Glib::ustring temp_uri = Utils::get_temp_file_uri("glom_printout", "html");
  std::cout << G_STRFUNC << ": temp_uri=" << temp_uri << std::endl;

  Glib::RefPtr<Gio::File> file = Gio::File::create_for_uri(temp_uri);
  Glib::RefPtr<Gio::FileOutputStream> stream;


  try
  {
    if(file->query_exists())
    {
      stream = file->replace();
    }
    else
    {


      stream = file->create_file();
    }
  }
  catch(const Gio::Error& ex)
  {

    return std::string();
  }


  gssize bytes_written = 0;
  const Glib::ustring::size_type result_bytes = contents.bytes();
  try
  {
    bytes_written = stream->write(contents.data(), result_bytes);
  }
  catch(const Gio::Error& ex)
  {

    return std::string();
  }

  if(bytes_written != (gssize)result_bytes)
    return std::string();

  return file->get_path();
}
