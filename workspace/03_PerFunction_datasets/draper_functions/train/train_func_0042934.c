offer_button_script_edit(const sharedptr<const LayoutItem_Button>& button)
{
  sharedptr<LayoutItem_Button> result;

  Dialog_ButtonScript* dialog = 0;
  Glom::Utils::get_glade_widget_derived_with_warning(dialog);
  if(!dialog)
    return result;

  dialog->set_script(button, m_table_name);
  dialog->set_transient_for(*this);
  const int response = Glom::Utils::dialog_run_with_help(dialog);
  dialog->hide();
  if(response == Gtk::RESPONSE_OK)
  {

     result = dialog->get_script();
  }

  delete dialog;

  return result;
}
