img_calc_slide_duration_points( GList *list,
								gint   length )
{
	GList        *tmp;
	gint          i, duration = 0;
	ImgStopPoint *point;


	if( length == 0 )
		return( 0 );


	for( tmp = list, i = 0; i < length; tmp = g_list_next( tmp ), i++ )
	{
		point = (ImgStopPoint *)tmp->data;
		duration += point->time;
	}

	return( duration );
}
