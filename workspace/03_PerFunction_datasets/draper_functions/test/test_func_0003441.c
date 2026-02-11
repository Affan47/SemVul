isFinite() const
{
	for (int i = 0; i < numRows(); i++)
		for (int j = 0; j < numCols(); j++)
			if (! std::isfinite(get(i,j)))
				return false;
	return true;
}
