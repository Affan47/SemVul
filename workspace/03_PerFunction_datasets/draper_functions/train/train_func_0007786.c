print_paths(const std::list<edge2d>& edges,
				  const pair& offset,
				  const std::string& attribs,
				  const std::string& len) const
  {
    std::stringstream obuf;

    std::list<edge2d>::const_iterator ep(edges.begin());

    const pair shift(pt_to_len(offset, len));

    bool all_visible(true);


    const std::string pname(start_open_path(attribs));


    while (ep != edges.end())
      {
	if ((*ep).is_seen())
	  {
	    obuf << pname
		 << print((*ep).tail() + shift)
		 << path_connector()
		 << print((*ep).head() + shift);
	    ++ep;

	    while ((*ep).is_seen() && ep != edges.end())
	      obuf << path_connector() << print((*ep++).head() + shift);

	    obuf << end_open_path(attribs);
	  }

	else
	  {
	    ++ep;
	    all_visible = false;
	  }
      }

    std::string value(obuf.str());

    --ep;


    if (all_visible && (*edges.begin()).tail() == (*ep).head())
      {
	value.replace(0,
		      start_open_path(attribs).size(),
		      start_closed_path(attribs));

	value.replace(value.size()-end_open_path(attribs).size(),
		      end_open_path(attribs).size(),
		      end_closed_path(attribs));
      }

    return break_lines(value, path_break());
  }
