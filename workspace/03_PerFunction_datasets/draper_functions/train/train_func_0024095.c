store_results(double x)
{
  int ii = 0;
  for (PROBELIST::const_iterator
	 p=storelist().begin();  p!=storelist().end();  ++p) {
    _sim->_waves[ii++].push(x, p->value());
  }
}
