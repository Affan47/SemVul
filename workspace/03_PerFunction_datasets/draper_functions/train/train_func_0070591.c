print_fill(const std::list<edge2d>& edges,
				const pair& offset,
				const Color& fc,
				const pen_data& line,
				const std::string& len) const
  {
    std::stringstream obuf;


    const double hatch_angle(m_hatch);
    m_hatch += d_hatch_theta;


    double dens(fc.alpha());
    if (dens < EPIX_EPSILON)
      return "";


    length hatch_width(length(PLAIN_WIDTH).to(len));

    path_state style;

    if (EPIX_EPSILON < dens*hatch_width.magnitude())
      {


	pen_data fill_pen(fc, (1-sqrt(1-dens))*hatch_width);


	hatch_data bd1(hatch_angle, hatch_width.magnitude(), edges);
	for (unsigned int i=0; i < bd1.data().size(); ++i)
	  obuf << format::print_line(bd1.data().at(i), offset,
				     fill_pen, style, std::string(""), len);


	hatch_data bd2(hatch_angle+90, hatch_width.magnitude(), edges);
	for (unsigned int i=0; i < bd2.data().size(); ++i)
	  obuf << format::print_line(bd2.data().at(i), offset,
				     fill_pen, style, "", len);
      }

    obuf << set_pen_state(line);
    obuf << print_paths(edges, offset, "", len);

    return obuf.str();
  }
