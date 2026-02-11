next_phase(int phase, int eid, Vector<int> &new_sigid,
		       const ProcessingT &pt)
{
  ElementT *e = const_cast<ElementT *>(_router->element(eid));
  int old_sigid = _sigid[eid];
  if (old_sigid == SIG_NOT_SPECIAL
      || _sigs[old_sigid]._connections.size() == 0) {
    new_sigid[eid] = old_sigid;
    return false;
  }


  Vector<int> new_connections;
  int ni = e->ninputs(), no = e->noutputs();
  for (int i = 0; i < ni; i++)
      if (pt.input_is_pull(eid, i)) {
	  const PortT &h = _router->find_connection_to(PortT(e, i));
	  if (h.element)
	      new_connections.push_back(_sigid[h.eindex()]);
      }
  for (int i = 0; i < no; i++)
      if (pt.output_is_push(eid, i)) {
	  const PortT &h = _router->find_connection_from(PortT(e, i));
	  if (h.element)
	      new_connections.push_back(_sigid[h.eindex()]);
      }


  if (_sigs[old_sigid]._phase != phase) {

    _sigs[old_sigid]._phase = phase;
    _sigs[old_sigid]._connections.swap(new_connections);
    _sigs[old_sigid]._next = -1;
    new_sigid[eid] = old_sigid;
    return false;
  }


  int prev = -1, trav = old_sigid;
  while (trav >= 0) {
    if (memcmp(&_sigs[trav]._connections[0], &new_connections[0],
	       new_connections.size() * sizeof(int)) == 0) {
      new_sigid[eid] = trav;
      return false;
    }
    prev = trav;
    trav = _sigs[trav]._next;
  }


  _sigs.push_back(SignatureNode(eid));
  SignatureNode &new_node = _sigs.back();
  new_node._phase = phase;
  new_node._connections.swap(new_connections);
  new_sigid[eid] = _sigs[prev]._next = _sigs.size() - 1;
  return true;
}
