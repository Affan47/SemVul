icmRGBprim2matrix(
	icmXYZNumber white,
	icmXYZNumber red,
	icmXYZNumber green,
	icmXYZNumber blue,
	double mat[3][3]
) {
	double tmat[3][3];
	double t[3];


	tmat[0][0] = red.X;
	tmat[0][1] = green.X;
	tmat[0][2] = blue.X;
	tmat[1][0] = red.Y;
	tmat[1][1] = green.Y;
	tmat[1][2] = blue.Y;
	tmat[2][0] = red.Z;
	tmat[2][1] = green.Z;
	tmat[2][2] = blue.Z;


	if (icmInverse3x3(mat, tmat))
		return 1;


	t[0] = mat[0][0] * white.X
	     + mat[0][1] * white.Y
	     + mat[0][2] * white.Z;
	t[1] = mat[1][0] * white.X
	     + mat[1][1] * white.Y
	     + mat[1][2] * white.Z;
	t[2] = mat[2][0] * white.X
	     + mat[2][1] * white.Y
	     + mat[2][2] * white.Z;


	mat[0][0] = red.X   * t[0];
	mat[0][1] = green.X * t[1];
	mat[0][2] = blue.X  * t[2];
	mat[1][0] = red.Y   * t[0];
	mat[1][1] = green.Y * t[1];
	mat[1][2] = blue.Y  * t[2];
	mat[2][0] = red.Z   * t[0];
	mat[2][1] = green.Z * t[1];
	mat[2][2] = blue.Z  * t[2];

	return 0;
}
