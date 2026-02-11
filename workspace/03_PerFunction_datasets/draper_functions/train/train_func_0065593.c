wrap_free_entry_internal(WrapperEntry *e)
{
    free (e->wildCard);
    if (e->tocvsFilter)
	free (e->tocvsFilter);
    if (e->fromcvsFilter)
	free (e->fromcvsFilter);
    if (e->rcsOption)
	free (e->rcsOption);
}
