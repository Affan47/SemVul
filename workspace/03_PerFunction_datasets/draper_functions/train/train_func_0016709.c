print_common_obsolete_callback(OMSTREAM& o, LANGUAGE* lang)const
{
  assert(lang);
  o << name() << '(';
  for (std::vector<std::pair<PARAMETER<double>,PARAMETER<double> > >::
	 const_iterator p = _table.begin();  p != _table.end();  ++p) {
    o << p->first << ',' << p->second << ' ';
  }
  o << ')';
  print_pair(o, lang, "order", _order);
  print_pair(o, lang, "below", _below, _below.has_hard_value());
  print_pair(o, lang, "above", _above, _above.has_hard_value());
  print_pair(o, lang, "delta", _delta, _delta.has_hard_value());
  print_pair(o, lang, "smooth",_smooth,_smooth.has_hard_value());
  EVAL_BM_ACTION_BASE::print_common_obsolete_callback(o, lang);
}
