define_units( std::string& new_m, std::string& new_l ) {

        if     ( new_m == "MEV" ) m_momentum_unit = Units::MEV ;
	else if( new_m == "GEV" ) m_momentum_unit = Units::GEV ;
	else std::cerr << "GenEvent::define_units ERROR: use either MEV or GEV\n";

        if     ( new_l == "MM" ) m_position_unit = Units::MM ;
	else if( new_l == "CM" ) m_position_unit = Units::CM ;
	else std::cerr << "GenEvent::define_units ERROR: use either MM or CM\n";

    }
