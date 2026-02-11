csq_cmdseq_row_delete_all(CmdSeq *cs)
{
	GList	*iter;

	if(cs == NULL)
		return;


	for(iter = cs->rows; iter != NULL; iter = g_list_next(iter))
		csq_cmdrow_destroy(iter->data);
	g_list_free(cs->rows);
	cs->rows = NULL;
}
