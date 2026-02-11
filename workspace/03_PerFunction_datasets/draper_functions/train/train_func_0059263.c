operator== (const Matrix &other) const
{
	unsigned int i, j;

	if (rep == other.rep)
		return true;
	if ((rep->rows != other.rep->rows) ||
	    (rep->columns != other.rep->columns))
		return false;

	for (j = 0; j < rep->rows; ++j)
		for (i = 0; i < rep->columns; ++i)
			if ((*this) (i, j) != other (i, j))
				return false;
	return true;
}
