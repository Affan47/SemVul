operator>>(std::istream &is, archive_node &n)
{

	unsigned num_props = read_unsigned(is);
	n.props.resize(num_props);
	for (unsigned i=0; i<num_props; i++) {
		unsigned name_type = read_unsigned(is);
		n.props[i].type = (archive_node::property_type)(name_type & 7);
		n.props[i].name = name_type >> 3;
		n.props[i].value = read_unsigned(is);
	}
	return is;
}
