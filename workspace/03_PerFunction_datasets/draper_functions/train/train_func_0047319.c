QCC_PR_IncludeChunkEx (char *data, pbool duplicate, char *filename, CompilerConstant_t *cnst)
{
	qcc_includechunk_t *chunk = qccHunkAlloc(sizeof(qcc_includechunk_t));
	chunk->prev = currentchunk;
	currentchunk = chunk;

	chunk->currentdatapoint = pr_file_p;
	chunk->currentlinenumber = pr_source_line;
	chunk->cnst = cnst;
	if( cnst )
	{
		cnst->inside++;
	}

	if (duplicate)
	{
		pr_file_p = qccHunkAlloc(strlen(data)+1);
		strcpy(pr_file_p, data);
	}
	else
		pr_file_p = data;
}
