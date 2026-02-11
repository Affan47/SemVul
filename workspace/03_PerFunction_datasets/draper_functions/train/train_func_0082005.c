CopyFrom(const TreeValue* v)
	{
		const TreeList* src = TreeValueCast<TreeList> (v);
		if (src != NULL)
		{
			Clear();
			elementname = src->ElementName();
			for (std::vector<TreeValue*>::const_iterator i( src->ElementArray().begin() ); i != src->ElementArray().end(); i++)
			{
				if ( (*i) == NULL )
				{
					Add(NULL);
				}
				else
				{
					TreeValue* element = ( *i )->NewBlank();
					element->CopyFrom( *i );
					Add(element);
				}
			}
		}
	}
