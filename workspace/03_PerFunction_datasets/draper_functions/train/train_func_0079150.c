on_parser_have_display_name(const Glib::ustring& display_name)
{
  set_title( Glib::ustring::compose(_("Import From CSV File: %1"), display_name) );
}
