read_param(Element *e, void *thunk)
{
    LinkUnqueue *u = (LinkUnqueue *)e;
    switch ((intptr_t) thunk) {
      case H_LATENCY:
	return u->_latency.unparse_interval();
      case H_BANDWIDTH:
	return String(u->_bandwidth * 100);
      case H_SIZE:
	return String(u->Storage::size());
      default:
	return "<error>";
    }
}
