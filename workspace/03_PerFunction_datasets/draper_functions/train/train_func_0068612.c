e_memchunk_destroy (EMemChunk *memchunk)
{
	gint i;

	if (memchunk == NULL)
		return;

	for (i = 0; i < memchunk->blocks->len; i++)
		g_free (memchunk->blocks->pdata[i]);

	g_ptr_array_free (memchunk->blocks, TRUE);

	g_free (memchunk);
}
