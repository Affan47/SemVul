cd_mat33_normalize (const CdMat3x3 *src, CdMat3x3 *dest)
{
	gdouble *data_dest;
	gdouble *data_src;
	gdouble det;
	guint i;

	data_src = cd_mat33_get_data (src);
	data_dest = cd_mat33_get_data (dest);
	det = cd_mat33_determinant (src);
	for (i = 0; i < 9; i++)
		data_dest[i] = data_src[i] / det;
}
