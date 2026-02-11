tr_advance()
{
  ELEMENT::tr_advance();

  const COMMON_SWITCH* c = prechecked_cast<const COMMON_SWITCH*>(common());
  assert(c);
  const MODEL_SWITCH* m = prechecked_cast<const MODEL_SWITCH*>(c->model());
  assert(m);

   _state[1] = _state[0];
  _y[0].x = _in[1] = _in[0];

  if (_y[0].x >= m->von) {
    _state[0] = _ON;
  }else if (_y[0].x <= m->voff) {
    _state[0] = _OFF;
  }else{
    _state[0] = _state[1];
  }

  if (_state[1] != _state[0]) {
    _y[0].f1 = (_state[0] == _ON) ? m->ron : m->roff;
    _m0.c1 = 1./_y[0].f1;
    q_eval();
  }else{
  }

  assert(_y[0].f1 == ((_state[0] == _ON) ? m->ron : m->roff));
  assert(_y[0].f0 == LINEAR);
  trace4("", _m0.c1, 1./_y[0].f1, ((_m0.c1) - (1./_y[0].f1)), ((_m0.c1) / (1./_y[0].f1)));
  assert(conchk(_m0.c1, 1./_y[0].f1));
  assert(_m0.c0 == 0.);
  set_converged();
}
