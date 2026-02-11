get_portal_relationship()
{
  Dialog_ChooseRelationship* dialog = 0;
  Utils::get_glade_widget_derived_with_warning(dialog);
  if(!dialog)
    return sharedptr<LayoutItem_Portal>();

  Document* pDocument = static_cast<Document*>(get_document());
  dialog->set_document(pDocument, m_table_name);

  const int response = dialog->run();
  dialog->hide();
  if(response == Gtk::RESPONSE_OK)
  {

    sharedptr<Relationship> relationship  = dialog->get_relationship_chosen();
    if(relationship)
    {
      sharedptr<LayoutItem_Portal> layout_item = sharedptr<LayoutItem_Portal>::create();
      layout_item->set_relationship(relationship);
      delete dialog;
      return layout_item;
    }
  }

  delete dialog;
  return sharedptr<LayoutItem_Portal>();
}
