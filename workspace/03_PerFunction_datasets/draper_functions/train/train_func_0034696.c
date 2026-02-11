apol_netifcon_query_destroy(apol_netifcon_query_t ** n)
{
	if (*n != NULL) {
		free((*n)->dev);
		apol_context_destroy(&((*n)->if_context));
		apol_context_destroy(&((*n)->msg_context));
		free(*n);
		*n = NULL;
	}
}
