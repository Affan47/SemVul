top10_delete_stat (gint i, gboolean locally)
{
	gint j;
	Statistics *top10;

	top10 = locally ? top10_local : top10_global;

	if (i > 9)
		return;

	for (j = i; j < 9; j++)
		memmove (&top10[j], &top10[j + 1], sizeof (Statistics));

	top10_clean_stat (9, locally);
}
