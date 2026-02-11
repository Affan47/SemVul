tr_eval(ELEMENT* d)const
{
  double x_raw = ioffset(d->_y[0].x);
  trace1("before", x_raw);
  double x = (x_raw < 0)
    ? ((_odd || _even) ? -x_raw : 0.)
    : x_raw;
  assert(x >= 0);
  trace1("rev", x);

  double f0 = 0.;
  double f1 = 0.;
  if (x > 0) {
    for (std::vector<std::pair<PARAMETER<double>,PARAMETER<double> > >::
	   const_iterator p = _table.begin();  p != _table.end();  ++p) {
      double coeff = p->second * pow(x, p->first-1);
      f1 += coeff * p->first;
      f0 += coeff * x;
    }
  }else{
    assert(x == 0);
    for (std::vector<std::pair<PARAMETER<double>,PARAMETER<double> > >::
	   const_iterator p = _table.begin();  p != _table.end();  ++p) {
      if (p->first == 0.) {
	f0 += 1;
	untested();
      }
    }
  }

  trace3("", x, f0, f1);

  if (_odd && x_raw < 0) {
    f0 = -f0;
  }
  if (_even && x_raw < 0) {
    f1 = -f1;
    untested();
  }
  trace3("after", x, f0, f1);

  if (_abs && f0 < 0) {
    f0 = -f0;
    f1 = -f1;
    untested();
  }

  if (f0 > _max) {
    f0 = _max;
    f1 = 0;
    untested();
  }else if (f0 < _min) {
    f0 = _min;
    f1 = 0;
    untested();
  }

  d->_y[0] = FPOLY1(x_raw, f0, f1);
  tr_final_adjust(&(d->_y[0]), d->f_is_value());
  trace3("fa", d->_y[0].x, d->_y[0].f0, d->_y[0].f1);
}
