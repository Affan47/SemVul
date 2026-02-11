remove(MemAreaPtr *area_ptr[])
{
  word_t addr;
  mem_area_list_t::iterator it;

  for (it = _l.begin();it != _l.end();it++)
    {
      addr = (*it)->get_addr() / MemArea::PAGE_SIZE;
      area_ptr[addr]->remove(*it);
    }
  _l.erase(_l.begin(), _l.end());
}
