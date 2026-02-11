do_tr()
{
  if (using_tr_eval()) {
    _y[0].x = _m0.x = tr_involts_limited();


    tr_eval();
    assert(_y[0].f0 != LINEAR);
    store_values();
    q_load();
    _m0 = CPOLY1(_y[0]);
    _m0 *= -_loss0;
  }else{
    assert(conchk(_loss0, 1./OPT::shortckt));
    assert(_y[0].f0 == LINEAR);
    assert(_y[0].f1 == value());
    assert(conchk(_m0.c1, -_loss0 * _y[0].f1));
    assert(_m0.c0 == 0.);
    assert(_y1 == _y[0]);
    assert(converged());
  }
  return converged();
}
