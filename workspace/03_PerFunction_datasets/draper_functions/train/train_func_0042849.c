annGaussPts(
	ANNpointArray		pa,
	int					n,
	int					dim,
	double				std_dev)
{
	for (int i = 0; i < n; i++) {
		for (int d = 0; d < dim; d++) {
			pa[i][d] = (ANNcoord) (annRanGauss() * std_dev);
		}
	}
}
