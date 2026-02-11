GetCoords (double* x, double* y, double *z) const
{
	if (x == NULL || y == NULL)
		return false;
	*x = m_x;
	*y = m_y;
	if (z)
		*z = 0.;
	return true;
}
