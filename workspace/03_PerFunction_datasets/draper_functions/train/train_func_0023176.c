info(void)
{
  mem_area_list_t::iterator it;


  for (it = _l.begin();it != --(_l.end());it++)
    {
      cerr << " [\"" << (*it)->get_name() << "\" "
	   << ((*it)->is_active() ? 'A' : 'a')
	   << ((*it)->is_readonly() ? 'R' : 'r')
	   << " ]";
    }
}
