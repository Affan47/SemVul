set_rotation_hotspot( CL_Origin origin, float x, float y )
{

	CL_Origin trans_origin = impl->translation_origin;
	set_alignment(origin_center);


	float angle = impl->angle;
	impl->set_angle(0.0f);

	float fix_x = 0, fix_y = 0;


	if( origin != origin_center )
	{
		float width = float(impl->width)/2;
		float height = float(impl->height)/2;

		switch( origin )
		{
		 case origin_top_left:
			fix_x = -width;
			fix_y = -height;
			break;
		 case origin_top_center:
			fix_x = 0;
			fix_y = -height;
			break;
		 case origin_top_right:
			fix_x = width;
			fix_y = -height;
			break;

		 case origin_center_left:
			fix_x = -width;
			fix_y = 0;
			break;
		 case origin_center:
			fix_x = 0;
			fix_y = 0;
			break;
		 case origin_center_right:
			fix_x = width;
			fix_y = 0;
			break;

		 case origin_bottom_left:
			fix_x = -width;
			fix_y = height;
			break;
		 case origin_bottom_center:
			fix_x = 0;
			fix_y = height;
			break;
		 case origin_bottom_right:
			fix_x = width;
			fix_y = height;
			break;
		}
	}

	impl->rotation_origin = origin;

	impl->rotation_hotspot.x = fix_x + x;
	impl->rotation_hotspot.y = fix_y + y;


	impl->set_angle(angle);

	set_alignment(trans_origin);

	impl->calculate_radius();
}
