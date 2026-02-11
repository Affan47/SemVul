unit()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (i == j)
				get(i,j) = 1.0;
			else
				get(i,j) = 0.0;
}
