skip_over_push(RouterT *r, const PortT &old_to, const PortT &new_to)
{
  Vector<int> connv;
  r->find_connections_to(old_to, connv);
  for (int i = 0; i < connv.size(); i++)
    r->change_connection_to(connv[i], new_to);
}
