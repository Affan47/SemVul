clear(const string &new_root)
{
	CTRACE("Configuration::clear");

	if(xmltree!=0)
		delete xmltree;
	CTRACE("Configuration::clear - xmltree deleted");
	if(new_root.size())
		rootname=new_root;
	CTRACE("Configuration::clear - new root specified");
	xmltree = new XMLnode(rootname);
	CTRACE("Configuration::clear - fin");
}
