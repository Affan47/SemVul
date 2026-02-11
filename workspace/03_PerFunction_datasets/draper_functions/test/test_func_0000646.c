instance (int x, int y, double* progress)
{
	if (!ms_instance) ms_instance = new VectorField (x, y, progress);
	return ms_instance;
}
