update_subrect(struct v4l2_rect *rect, struct v4l2_rect *subrect)
{
	if (rect->width < subrect->width)
		subrect->width = rect->width;

	if (rect->height < subrect->height)
		subrect->height = rect->height;

	if (rect->left > subrect->left)
		subrect->left = rect->left;
	else if (rect->left + rect->width >
		 subrect->left + subrect->width)
		subrect->left = rect->left + rect->width -
			subrect->width;

	if (rect->top > subrect->top)
		subrect->top = rect->top;
	else if (rect->top + rect->height >
		 subrect->top + subrect->height)
		subrect->top = rect->top + rect->height -
			subrect->height;
}
