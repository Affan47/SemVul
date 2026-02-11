ReadValue(XMLReadingMachine& reader, const pugi::xml_node& element) const
	{

		std::string xml_element_name;
		pugi::xml_node child;
		for (child = element.first_child(); child; child = child.next_sibling())
		{
			if (child.type() == pugi::node_element)
			{
				if (xml_element_name.empty())
				{

					xml_element_name = child.name();
				}
				else
				{

					if (xml_element_name.compare(child.name()) != 0)
						return NULL;
				}
			}
		}


		if (xml_element_name.empty())
			return NULL;


		std::auto_ptr<TreeList> newlist( new TreeList( xml_element_name.c_str() ) );


		for (child = element.first_child(); child; child = child.next_sibling())
		{
			if (child.type() == pugi::node_element)
			{
				TreeValue* newvalue = reader.ReadValue( child );
				if (newvalue != NULL)
				{
					newlist->Add( newvalue );
				}
				else
				{

				}
			}
		}

		return newlist.release();
	}
