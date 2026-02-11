_raw_xml(std::string &xml, int &depth) const
{
	xml.append(depth *2, ' ');
	xml.append("<"+name);

	for (Attributes::const_iterator i = _attrs.begin(); i != _attrs.end(); ++i)
	{
		xml.append(" "+i->first+"=\""+i->second+"\"");
	}

	if (cdata.length() == 0 && children.size() == 0)
	{
		xml.append("/>\n");
	}
	else
	{
		xml.append(">");

		if (cdata.length())
		{
			xml.append(cdata);
		}

		if (children.size())
		{
			xml.append("\n");
			depth++;

			for (Children::const_iterator i = children.begin(); i != children.end(); ++i)
			{
				i->_raw_xml(xml, depth);
			}

			depth--;
			xml.append(depth *2, ' ');
		}
		xml.append("</"+name+">\n");
	}
}
