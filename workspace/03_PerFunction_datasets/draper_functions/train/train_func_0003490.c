anjuta_print_job_info_destroy(PrintJobInfo *pji)
{
	int i;

	g_return_if_fail (pji);

	if (pji->pages != NULL)
		g_array_free (pji->pages, TRUE);

	if (pji->layout != NULL)
		g_object_unref (pji->layout);

	if (pji->line_numbers_layout != NULL)
		g_object_unref (pji->line_numbers_layout);

	if (pji->header_layout != NULL)
		g_object_unref (pji->header_layout);

	if (pji->buffer != NULL)
		g_free(pji->buffer);

	for (i = 0; i < AN_PRINT_MAX_STYLES; i++)
	{
		if (pji->styles_pool[i])
			anjuta_print_job_info_style_destroy (pji->styles_pool[i]);
	}
	g_free(pji);
}
