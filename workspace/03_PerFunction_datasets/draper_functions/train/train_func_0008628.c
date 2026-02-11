response_print_errors(const char *context,
				SPF_response_t *spf_response, SPF_errcode_t err)
{
	SPF_error_t	*spf_error;
	int			 i;

	if (context != NULL)
		printf("Context: %s\n", context);
	if (err != SPF_E_SUCCESS)
		printf("ErrorCode: (%d) %s\n", err, SPF_strerror(err));

	if (spf_response != NULL) {
		for (i = 0; i < SPF_response_messages(spf_response); i++) {
			spf_error = SPF_response_message(spf_response, i);
			printf( "%s: %s%s\n",
					SPF_error_errorp(spf_error) ? "Error" : "Warning",
					((SPF_error_errorp(spf_error) && (!err))
							? "[UNRETURNED] "
							: ""),
					SPF_error_message(spf_error) );
		}
	}
	else {
		printf("Error: libspf2 gave a NULL spf_response");
	}
}
