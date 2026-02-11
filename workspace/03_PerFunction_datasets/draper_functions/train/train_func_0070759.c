anchor_next(void)
{
	if (!start)
		return NULL;
	if (++CURRENT >= end)
		return NULL;
	if (CURRENT->type == 'D')
		CURRENTDEF = CURRENT;
	return CURRENT;
}
