_build_job_list( char* str )
{
	List my_list;
	char *job = NULL, *tmp_char = NULL, *my_job_list = NULL;
	int i;
	uint32_t *job_id = NULL;

	if ( str == NULL)
		return NULL;
	my_list = list_create( NULL );
	my_job_list = xstrdup( str );
	job = strtok_r( my_job_list, ",", &tmp_char );
	while (job)
	{
		i = strtol( job, (char **) NULL, 10 );
		if (i <= 0) {
			error( "Invalid job id: %s", job );
			exit( 1 );
		}
		job_id = xmalloc( sizeof( uint32_t ) );
		*job_id = (uint32_t) i;
		list_append( my_list, job_id );
		job = strtok_r (NULL, ",", &tmp_char);
	}
	return my_list;
}
