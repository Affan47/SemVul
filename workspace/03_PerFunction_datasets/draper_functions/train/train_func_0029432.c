clear_ptr()
{
	Unit::clear_ptr();

	if( !cast_power_type )
	{
		cast_origin_x = 0;
		cast_origin_y = 0;
		cast_target_x = 0;
		cast_target_y = 0;
	}

}
