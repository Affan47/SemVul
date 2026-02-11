write_units( std::ostream & os ) const {
	os << " Momenutm units:" << std::setw(8) << name(momentum_unit());
	os << "     Position units:" << std::setw(8) << name(length_unit());
	os << std::endl;
    }
