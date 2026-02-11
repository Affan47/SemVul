cd_mat33_matrix_multiply (const CdMat3x3 *mat_src1, const CdMat3x3 *mat_src2, CdMat3x3 *mat_dest)
{
	guint8 i, j, k;
	gdouble *src1 = cd_mat33_get_data (mat_src1);
	gdouble *src2 = cd_mat33_get_data (mat_src2);
	gdouble *dest = cd_mat33_get_data (mat_dest);
	g_return_if_fail (mat_src1 != mat_dest);
	g_return_if_fail (mat_src2 != mat_dest);

	cd_mat33_clear (mat_dest);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				dest[3 * i + j] += src1[i * 3 + k] * src2[k * 3 + j];
			}
		}
	}
}
