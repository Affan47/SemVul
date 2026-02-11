printraw(std::ostream &os) const
{

	os << "Atoms:\n";
	{
		std::vector<std::string>::const_iterator i = atoms.begin(), iend = atoms.end();
		archive_atom id = 0;
		while (i != iend) {
			os << " " << id << " " << *i << std::endl;
			i++; id++;
		}
	}
	os << std::endl;


	os << "Expressions:\n";
	{
		std::vector<archived_ex>::const_iterator i = exprs.begin(), iend = exprs.end();
		unsigned index = 0;
		while (i != iend) {
			os << " " << index << " \"" << unatomize(i->name) << "\" root node " << i->root << std::endl;
			i++; index++;
		}
	}
	os << std::endl;


	os << "Nodes:\n";
	{
		std::vector<archive_node>::const_iterator i = nodes.begin(), iend = nodes.end();
		archive_node_id id = 0;
		while (i != iend) {
			os << " " << id << " ";
			i->printraw(os);
			i++; id++;
		}
	}
}
