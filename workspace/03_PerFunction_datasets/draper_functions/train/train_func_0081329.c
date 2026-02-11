icmChromAdaptMatrix(
	int flags,
	icmXYZNumber d_wp,
	icmXYZNumber s_wp,
	double mat[3][3]
) {
	double dst[3], src[3];
	double vkmat[3][3];
#ifdef NEVER
	static double bradford[3][3] = {
		{  1.0,  0.0, 0.0 },
		{  0.0,  1.0, 0.0 },
		{  0.0,  0.0, 1.0 }
	};
#endif
	static double bradford[3][3] = {
		{  0.8951,  0.2664, -0.1614 },
		{ -0.7502,  1.7135,  0.0367 },
		{  0.0389, -0.0685,  1.0296 }
	};
	static int inited = 0;
	static double ibradford[3][3];


	if (!(flags & ICM_CAM_MULMATRIX)) {
		icmSetUnity3x3(mat);
	}

	icmXYZ2Ary(src, s_wp);
	icmXYZ2Ary(dst, d_wp);

	if (flags & ICM_CAM_BRADFORD) {
		icmMulBy3x3(src, bradford, src);
		icmMulBy3x3(dst, bradford, dst);
	}


	vkmat[0][0] = dst[0]/src[0];
	vkmat[1][1] = dst[1]/src[1];
	vkmat[2][2] = dst[2]/src[2];
	vkmat[0][1] = vkmat[0][2] = 0.0;
	vkmat[1][0] = vkmat[1][2] = 0.0;
	vkmat[2][0] = vkmat[2][1] = 0.0;


	if (flags & ICM_CAM_BRADFORD) {
		icmMul3x3(mat, bradford);
	}


	icmMul3x3(mat, vkmat);


	if (flags & ICM_CAM_BRADFORD) {
		if (inited == 0) {
			icmInverse3x3(ibradford, bradford);
			inited = 1;
		}
		icmMul3x3(mat, ibradford);
	}


}
