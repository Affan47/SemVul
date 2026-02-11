get_mime_type() const
{
  const GdaBinary* gda_binary = get_binary();

  if(!gda_binary)
    return Glib::ustring();

  if(!gda_binary->data)
    return Glib::ustring();

  bool uncertain = false;
  const Glib::ustring result = Gio::content_type_guess(std::string(),
    gda_binary->data, gda_binary->binary_length,
    uncertain);


  return result;
}
