sensor_exists( unsigned int id )
{
	int i;

	pthread_mutex_lock( &the_mutex );
        for( i = 0; i < MAX_SENSOR; i++ )
        {
                if( added_sensors[i] == id )
                        break;
        }
        pthread_mutex_unlock( &the_mutex );

	return i;
}
