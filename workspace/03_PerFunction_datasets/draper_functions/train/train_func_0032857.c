get_wing_index(object *objp, int wingnum)
{
	wing	*wingp;
	int	i;

	Assert((wingnum >= 0) && (wingnum < MAX_WINGS));

	wingp = &Wings[wingnum];

	for (i=wingp->current_count-1; i>=0; i--)
		if ( objp->instance == wingp->ship_index[i] )
			break;

	return i;
}
