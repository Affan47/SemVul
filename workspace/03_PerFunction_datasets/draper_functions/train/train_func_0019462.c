ply_put_element_setup(PlyFile *plyfile, const string &elem_name)
{
  PlyElement *elem;

  elem = find_element (plyfile, elem_name);
  if (elem == NULL)
	  throw std::runtime_error(format("ply_elements_setup: can't find element '%s'", elem_name.c_str()));

  plyfile->which_elem = elem;
}
