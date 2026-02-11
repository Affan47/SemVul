want_input()
{
  int ne = _icount.size();
  for (int i = 0; i < ne; i++) {
      Traits t = element_map.traits(_router->etype_name(i));
      _aligners[i]->want_flow(_ialign.begin() + _ioffset[i], _icount[i],
			      _oalign.begin() + _ooffset[i], _ocount[i],
			      _router->element(i)->flow_code());
  }
}
