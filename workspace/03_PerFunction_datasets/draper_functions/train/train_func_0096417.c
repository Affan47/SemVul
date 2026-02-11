getNorm1() const
{
	double norm = 0.0;
	for (int j = 0; j < numCols(); j++) {
		ConstVector colj(data.base()+ld*j, 1, rows);
		double normj = colj.getNorm1();
		if (norm < normj)
			norm = normj;
	}
	return norm;
}
