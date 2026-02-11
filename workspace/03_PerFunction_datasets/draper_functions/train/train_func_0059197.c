operator*(Matrix2D& cMat)
{
	static Matrix2D cMat0;
	Matrix2D m(
			x[0][0] * cMat.x[0][0] + x[0][1] * cMat.x[1][0],
			x[0][0] * cMat.x[0][1] + x[0][1] * cMat.x[1][1],
			x[1][0] * cMat.x[0][0] + x[1][1] * cMat.x[1][0],
			x[1][0] * cMat.x[0][1] + x[1][1] * cMat.x[1][1]
		);
	return cMat0 = m;
}
