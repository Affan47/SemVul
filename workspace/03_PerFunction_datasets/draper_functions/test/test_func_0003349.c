find_connections(const Hookup &this_end, bool is_out,
			Vector<Hookup> &into) const
{
  const Vector<Hookup> &hookup_this(is_out ? _c->_hookup_from : _c->_hookup_to);
  const Vector<Hookup> &hookup_that(is_out ? _c->_hookup_to : _c->_hookup_from);
  for (int i = 0; i < hookup_this.size(); i++)
    if (hookup_this[i] == this_end)
      into.push_back(hookup_that[i]);
}
