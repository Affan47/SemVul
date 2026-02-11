value() const
	{
		return (_root && _root->value) ? _root->value : PUGIXML_TEXT("");
	}
