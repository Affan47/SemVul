gf_rect_overlaps(GF_Rect rc1, GF_Rect rc2)
{
	if (! rc2.height || !rc2.width || !rc1.height || !rc1.width) return 0;
	if (rc2.x+rc2.width<=rc1.x) return 0;
	if (rc2.x>=rc1.x+rc1.width) return 0;
	if (rc2.y-rc2.height>=rc1.y) return 0;
	if (rc2.y<=rc1.y-rc1.height) return 0;
	return 1;
}
