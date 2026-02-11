zeros()
{
	if (ld == rows)
		data.zeros();
	else {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				get(i,j) = 0;
	}
}
