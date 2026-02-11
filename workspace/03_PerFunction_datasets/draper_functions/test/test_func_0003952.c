print() const
{

    for (std::map<std::string, Variable*>::const_iterator map_it = configuration->begin ();
	 map_it != configuration->end ();
	 map_it++) {


	std::cout << map_it->first;


	std::cout << " = " << map_it->second->get_value () << std::endl;
    }
}
