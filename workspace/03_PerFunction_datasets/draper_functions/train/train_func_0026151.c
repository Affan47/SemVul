operator=(const Matrix& m2)
{
	int i, j;

	if(Nrows != m2.Nrows || Ncols != m2.Ncols){
		delete []row;
		setsize(m2.Nrows, m2.Ncols);
	}

	for(i = 0; i < Nrows; i++)
		for(j = 0; j < Ncols; j++)
			(row[i])[j] = (m2.row[i])[j];

	return (*this);
}
