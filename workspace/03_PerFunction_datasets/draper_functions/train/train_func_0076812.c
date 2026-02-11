ComputeRepresentativePoint(double *Quadric, double *Point
				,int MaxNumberOfUsedSingularValues, double SVThreshold)
{
	double tempVector[3];
	int RankDefficiency=vtkQuadricTools::ComputeDisplacement(Quadric,Point,
							tempVector,MaxNumberOfUsedSingularValues,SVThreshold);
	for	(int i = 0;	i <	3; i++)
		Point[i] += tempVector[i];
	return RankDefficiency;
}
