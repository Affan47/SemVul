add_sensor( unsigned int id )
{
	int i = 0;

	pthread_mutex_lock( &the_mutex );
	for( i = 0; i < MAX_SENSOR; i++ )
	{
		if( added_sensors[i] == 0 )
		{
			added_sensors[i] = id;
			sensor_count++;

			break;
		}
	}
	pthread_mutex_unlock( &the_mutex );
	if( i == MAX_SENSOR )
		return 1;

	return 0;
}
