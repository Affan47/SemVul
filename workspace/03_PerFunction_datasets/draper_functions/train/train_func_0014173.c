lcm(const vector<Rational> &v) {
    Rational::Impl g(1,1), zero;
    for(size_t i=0; i<v.size(); i++) {
      checkInt(v[i], "lcm(vector<Rational>)");
      if(*v[i].d_n != zero)
	g = lcm(g, *v[i].d_n);
    }
    return Rational(g);
  }
