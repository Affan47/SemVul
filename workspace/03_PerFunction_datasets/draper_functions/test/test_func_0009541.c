_build_user_list( char* str )
{
	List my_list;
	char *user = NULL;
	char *tmp_char = NULL, *my_user_list = NULL;

	if ( str == NULL )
		return NULL;
	my_list = list_create( NULL );
	my_user_list = xstrdup( str );
	user = strtok_r( my_user_list, ",", &tmp_char );
	while (user) {
		uid_t some_uid;
		if ( uid_from_string( user, &some_uid ) == 0 ) {
			uint32_t *user_id = NULL;
			user_id = xmalloc( sizeof( uint32_t ));
			*user_id = (uint32_t) some_uid;
			list_append( my_list, user_id );
		} else {
			error( "Invalid user: %s\n", user);
		}
		user = strtok_r (NULL, ",", &tmp_char);
	}
	return my_list;
}
