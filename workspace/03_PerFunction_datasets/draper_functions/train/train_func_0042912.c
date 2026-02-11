cd_color_xyz_dup (const CdColorXYZ *src)
{
	CdColorXYZ *dest;
	g_return_val_if_fail (src != NULL, NULL);
	dest = cd_color_xyz_new ();
	dest->X = src->X;
	dest->Y = src->Y;
	dest->Z = src->Z;
	return dest;
}
