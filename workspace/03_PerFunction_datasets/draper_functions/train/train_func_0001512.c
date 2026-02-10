ToTree() const
	{

		TreeCompound* cpy = new TreeCompound();
		for (std::vector<MapCompoundElement*>::const_iterator i( refmap.begin() ); i != refmap.end(); i++)
		{
			TreeValue* cpyvalue = (*i)->ToTree();
			if (cpyvalue != NULL)
			{
				cpy->Set((*i)->Name(), cpyvalue);
			}
		}
		return cpy;
	}
