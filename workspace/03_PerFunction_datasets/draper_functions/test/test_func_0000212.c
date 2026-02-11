printTableCleanup(printTableContent *const content)
{
	if (content->cellmustfree)
	{
		int			i;

		for (i = 0; i < content->nrows * content->ncolumns; i++)
		{
			if (content->cellmustfree[i])
				free((char *) content->cells[i]);
		}
		free(content->cellmustfree);
		content->cellmustfree = NULL;
	}
	free(content->headers);
	free(content->cells);
	free(content->aligns);

	content->opt = NULL;
	content->title = NULL;
	content->headers = NULL;
	content->cells = NULL;
	content->aligns = NULL;
	content->header = NULL;
	content->cell = NULL;
	content->align = NULL;

	if (content->footers)
	{
		for (content->footer = content->footers; content->footer;)
		{
			printTableFooter *f;

			f = content->footer;
			content->footer = f->next;
			free(f->data);
			free(f);
		}
	}
	content->footers = NULL;
	content->footer = NULL;
}
