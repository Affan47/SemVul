rect_overlap(const struct v4l2_rect *r1, const struct v4l2_rect *r2)
{


	if (r1->left >= r2->left + r2->width ||
	    r2->left >= r1->left + r1->width)
		return false;


	if (r1->top >= r2->top + r2->height ||
	    r2->top >= r1->top + r1->height)
		return false;
	return true;
}
