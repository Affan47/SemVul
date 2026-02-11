gdip_is_rect_infinite (GpRectF *rect)
{
	return (rect && (rect->X == REGION_INFINITE_POSITION) &&
		(rect->Y == REGION_INFINITE_POSITION) &&
		(rect->Width == REGION_INFINITE_LENGTH) &&
		(rect->Height == REGION_INFINITE_LENGTH));
}
