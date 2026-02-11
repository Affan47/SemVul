expand_connection(const Hookup &this_end, bool is_out,
			 Vector<Hookup> &into) const
{
  if (_c->_elements[this_end.idx] != TUNNEL_TYPE)
    into.push_back(this_end);
  else {
    TunnelEnd *dp = (is_out ? _defoutputs : _definputs);
    if (dp)
      dp = dp->find(this_end);
    if (dp)
      dp->expand(this, into);
    else if ((dp = (is_out ? _definputs : _defoutputs)->find(this_end)))
      _errh->lerror(_c->_element_landmarks[this_end.idx],
		    (is_out ? "'%s' used as output" : "'%s' used as input"),
		    element_name(this_end.idx).c_str());
  }
}
