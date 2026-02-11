getNumberOfChildren() const
{
	RefBaseAST t = this->down;
	size_t n = 0;
	if( t )
	{
		n = 1;
		while( t->right )
		{
			t = t->right;
			n++;
		}
		return n;
	}
	return n;
}
