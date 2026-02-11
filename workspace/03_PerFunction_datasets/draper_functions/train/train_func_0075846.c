delete_directory(const Glib::RefPtr<Gio::File>& directory)
{
  if(!(directory->query_exists()))
    return true;


  Glib::RefPtr<Gio::FileEnumerator> enumerator = directory->enumerate_children();

  Glib::RefPtr<Gio::FileInfo> info = enumerator->next_file();
  while(info)
  {
    Glib::RefPtr<Gio::File> child = directory->get_child(info->get_name());
    bool removed_child = false;
    if(child->query_file_type() == Gio::FILE_TYPE_DIRECTORY)
      removed_child = delete_directory(child);
    else
      removed_child = child->remove();

    if(!removed_child)
       return false;

    info = enumerator->next_file();
  }


  if(!directory->remove())
    return false;

  return true;
}
