connect(int from_idx, int from_port, int to_idx, int to_port)
{
  if (from_port < 0)
    from_port = 0;
  if (to_port < 0)
    to_port = 0;
  _conn.push_back(Router::Connection(from_idx, from_port, to_idx, to_port));
  if (_element_nports[0][to_idx] <= to_port)
    _element_nports[0][to_idx] = to_port + 1;
  if (_element_nports[1][from_idx] <= from_port)
    _element_nports[1][from_idx] = from_port + 1;
}
