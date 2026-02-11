gzip_continue_func (FrError  **error,
		    gpointer   user_data)
{


	if ((*error != NULL) && ((*error)->status == 2))
		fr_clear_error (error);

	return *error == NULL;
}
