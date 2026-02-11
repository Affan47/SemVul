to(std::string units)
  {
    units = units.substr(0,2);

    if (m_units == units)
      return *this;

    if (units == "pt")
      {
	m_mag *= pts_per_unit;
	pts_per_unit = 1.0;
	m_units = units;
      }

    else if (units == "in")
      {
	m_mag *= pts_per_unit/IN;
	pts_per_unit = IN;
	m_units = units;
      }

    else if (units == "cm")
      {
	m_mag *= pts_per_unit/CM;
	pts_per_unit = CM;
	m_units = units;
      }

    else if (units == "mm")
      {
	m_mag *= pts_per_unit/MM;
	pts_per_unit = MM;
	m_units = units;
      }

    else if (units == "pc")
      {
	m_mag *= pts_per_unit/PC;
	pts_per_unit = PC;
	m_units = units;
      }

    else if (units == "bp")
      {
	m_mag *= pts_per_unit/BP;
	pts_per_unit = BP;
	m_units = units;
      }


    else
      epix_warning("Ignoring conversion to unrecognized units \""+units+"\"");

    return *this;
  }
