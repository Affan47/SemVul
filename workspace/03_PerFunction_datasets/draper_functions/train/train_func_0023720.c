free_headers(http_header_t * headers) {
	if (headers == NULL)
		return;

	if (headers->status != NULL)
		free(headers->status);
	if (headers->location != NULL)
		free(headers->location);
	if (headers->content_type != NULL)
		free(headers->content_type);
	if (headers->transfer_encoding != NULL)
		free(headers->transfer_encoding);
	if (headers->icy_genre != NULL)
		free(headers->icy_genre);
	if (headers->icy_name != NULL)
		free(headers->icy_name);
	if (headers->icy_description != NULL)
		free(headers->icy_description);
}
