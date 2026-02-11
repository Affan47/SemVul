copy(const ConstGeneralMatrix& m, int ioff, int joff)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			get(i,j) = m.get(i+ioff,j+joff);
}
