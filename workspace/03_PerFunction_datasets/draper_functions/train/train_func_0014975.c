clear_entry ( user_entry *en)
{

	if( en->passwd != NULL ) {
		memset(en->passwd, 0, strlen(en->passwd) );
		free(en->passwd);
	}

	free(en->login);

}
