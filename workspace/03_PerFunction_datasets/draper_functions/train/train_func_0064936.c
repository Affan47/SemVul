cd_mat33_clear (const CdMat3x3 *src)
{
	guint i;
	gdouble *temp = (gdouble *) src;
	for (i = 0; i < 3*3; i++)
		temp[i] = 0.0f;
}
