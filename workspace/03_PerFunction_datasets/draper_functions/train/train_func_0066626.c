dump(ostream &o, const string &indentstr, const unsigned int depth) const
{

	for(unsigned int i=0; i<depth; i++)
		o << indentstr;


	o << '<' << id << '>';


	if(id[id.length()-1]!='/')
	{

		if(nodelist.size())
		{
			o << endl;


			for(std::vector<XMLnode *>::const_iterator it=nodelist.begin(); it!=nodelist.end(); ++it)
				(*it)->dump(o, indentstr, depth+1);
		}

		else if(content.length())
			o << ' ' << encode_entity(content) << ' ';


		if(id[0]=='?')
			return;


		if(!no_close)
		{

			if(nodelist.size())
			for(unsigned int i=0; i<depth; i++)
				o << indentstr;

			o << "</" << close_tag(id) << '>';
		}
	}
	o << endl;
}
