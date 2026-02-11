populate_menu_for_group (const std::string name,
				      Ekiga::MenuBuilder& builder)
{
  builder.add_action ("edit", _("Rename"),
		      boost::bind (&Local::Heap::on_rename_group, this, name));
  return true;
}
