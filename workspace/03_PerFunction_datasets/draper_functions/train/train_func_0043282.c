read_from_disk(int& failure_code)
{
  failure_code = LOAD_FAILURE_CODE_NONE;

  m_strContents.erase();


  if(m_file_uri.empty())
    return false;

  Glib::RefPtr<Gio::File> file = Gio::File::create_for_uri(m_file_uri);

  Glib::RefPtr<Gio::FileInputStream> stream;

  try
  {
    stream = file->read();
  }
  catch(const Gio::Error& ex)
  {
    std::cerr << G_STRFUNC << ": Error: " << ex.what() << std::endl;
    std::cerr << " with m_file_uri=" << m_file_uri << std::endl;


    if(ex.code() == Gio::Error::NOT_FOUND)
      failure_code = LOAD_FAILURE_CODE_NOT_FOUND;


    return false;
  }


  guint buffer[BYTES_TO_PROCESS] = {0, };
  gsize bytes_read = 0;
  std::string data;

  try
  {
    bool bContinue = true;
    while(bContinue)
    {
      bytes_read = stream->read(buffer, BYTES_TO_PROCESS);

      if(bytes_read == 0)
        bContinue = false;
      else
      {

        data += std::string((char*)buffer, bytes_read);
      }
    }
  }
  catch(const Gio::Error& ex)
  {

    return false;
  }

  m_strContents = data;

  set_modified(false);

  return true;
}
