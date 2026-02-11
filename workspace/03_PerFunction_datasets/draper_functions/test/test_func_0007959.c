add(MemArea *area)
{
  int prio;
  mem_area_list_t::iterator it;

  prio = area->get_prio();
  for (it = _l.begin();it != _l.end();it++)
    if ((*it)->get_prio() > prio) break;
  _l.insert(it, area);
}
