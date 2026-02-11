plot(double scale) const
  {
    if (m_pop == 0)
      return;


    __epix_out_of_range("data_bins::plot", m_lo_ct, m_hi_ct, m_cut_hits);


    std::vector<P> vertices;

    std::list<d_bin*>::const_iterator bn(m_bins.begin());
    vertices.push_back(P((*bn)->lo(),0));

    for (bn = m_bins.begin(); bn != m_bins.end(); ++bn)
      {
	vertices.push_back(P((*bn)->lo(), (*bn)->ht(scale/m_pop)));
	vertices.push_back(P((*bn)->hi(), (*bn)->ht(scale/m_pop)));
      }

    --bn;
    vertices.push_back(P((*bn)->hi(),0));

    const unsigned int N(vertices.size());


    line(vertices.at(0), 0.5*(vertices.at(0) + vertices.at(1)));


    for (unsigned int i=1; i< N-1; ++i)
      spline(0.5*(vertices.at(i-1) + vertices.at(i)),
	     vertices.at(i),
	     vertices.at(i),
	     0.5*(vertices.at(i) + vertices.at(i+1)), 20);

    line(0.5*(vertices.at(N-2) + vertices.at(N-1)), vertices.at(N-1));
  }
