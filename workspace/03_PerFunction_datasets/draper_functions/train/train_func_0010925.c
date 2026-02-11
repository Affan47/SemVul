next_day()
{

	season_phase = (season_phase + 1 )% 365;


	if( day_to_quake)
	{
		day_to_quake--;
		if ( is_quake() )
		{

			quake_x = rand_seed(0x10000) * MAX_MAP_WIDTH / 0x10000;
			quake_y = rand_seed(0x10000) * MAX_MAP_HEIGHT / 0x10000;
		}
	}
	else
		day_to_quake = quake_frequency + rand_seed(quake_frequency);


	wind_dir = (wind_dir + rand_seed(5) ) % 360;
	wind_spd += rand_seed(9) - 4 - (high_wind_day/16);
	if( wind_spd < -10)
		wind_spd = -10;
	if( wind_spd > 110)
		wind_spd = 110;
	if( wind_spd >= 20 )
	{
		high_wind_day++;
	}
	else
	{
		high_wind_day--;
	}


	if( cur_cloud_len > 0)
	{
		cur_cloud_len--;
	}
	else
	{
		short t = base_temp();
		short maxCloudStr;
		if( t >= 30)
			maxCloudStr = 10;
		else if( t <= 18)
			maxCloudStr = 4;
		else
			maxCloudStr = (t -18)/2 + 4;
		cur_cloud_str = rand_seed(maxCloudStr+4)-3;
		if(cur_cloud_str < 0)
			cur_cloud_str = 0;
		cur_cloud_len = 2 + rand_seed(3) + rand_seed(3);

		cur_cloud_type = 0;


		if( cur_cloud_str > 4)
		{
			if( (char) rand_seed(10) < cur_cloud_str )
				cur_cloud_type |= RAIN_CLOUD;
			if( cur_cloud_str >= 6 && (char) rand_seed(10) < cur_cloud_str-4)
				cur_cloud_type |= WINDY;
		}
		if( cur_cloud_str <= 1 && t >= 30 && rand_seed(10) <= 1)
		{
			cur_cloud_type |= HOT_WAVE;
		}


		if( t < 15)
		{
			if( rand_seed(20) < 2 )
				cur_cloud_type |= COLD_WAVE;

			if( t >= 10 && rand_seed(10) < 3)
				cur_cloud_type |= WINDY;
			if( t < 10 && rand_seed(10) < 7)
				cur_cloud_type |= WINDY;
		}
		if( cur_cloud_type & WINDY)
			windy_speed = 10 + cur_cloud_str * 5 + rand_seed(2*cur_cloud_str+1);
		else
		{
			windy_speed = 0;
			if( cur_cloud_str > 4 && (char)rand_seed(50) < cur_cloud_str + 2 )
				cur_cloud_type |= LIGHTNING_CLOUD;
		}


		if( snow_scale() )
			cur_cloud_len += cur_cloud_len;

	}


	if( tornado_count > 20 && base_temp() >= 30 && wind_speed() >= 40
		&& rand_seed(10)==0 )
	{
		tornado_count = 0;
	}
	else
	{
		tornado_count++;
	}
}
