wbcg_get_n_scg (WBCGtk const *wbcg)
{
	return (GTK_IS_NOTEBOOK (wbcg->snotebook))?
		gtk_notebook_get_n_pages (wbcg->snotebook): -1;
}
