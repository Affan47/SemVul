get_content(
                            const Glib::Date & date,
                            const gnote::NoteManager & manager)
{
  const std::string title = get_title(date);


  const gnote::Note::Ptr template_note = manager.find(
                                                   s_template_title);

  if (0 != template_note) {
    std::string xml_content = template_note->xml_content();
    return xml_content.replace(xml_content.find(s_template_title, 0),
                               s_template_title.length(),
                               title);
  }
  else {
    return get_template_content(title);
  }
}
