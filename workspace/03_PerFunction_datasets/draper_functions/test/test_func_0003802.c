hasSelfInDesc ( const DLTree* t ) const
{
	if ( t == NULL )
		return false;

	switch ( t->Element().getToken() )
	{
		case NAME:
		{
			const ClassifiableEntry* name = static_cast<const ClassifiableEntry*>(t->Element().getNE());
			return resolveSynonym(name) == this;
		}
		case AND:
			return hasSelfInDesc(t->Left()) || hasSelfInDesc(t->Right());
		case NOT:
			switch ( t->Left()->Element().getToken() )
			{
			case AND:
			case NAME:
				return hasSelfInDesc(t->Left());
			default:
				return false;
		}
		default:
			return false;
	}
}
