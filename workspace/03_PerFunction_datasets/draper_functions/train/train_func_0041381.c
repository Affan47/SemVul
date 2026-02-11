lpfc_sli_hbq_entry_count(void)
{
	int  hbq_count = lpfc_sli_hbq_count();
	int  count = 0;
	int  i;

	for (i = 0; i < hbq_count; ++i)
		count += lpfc_hbq_defs[i]->entry_count;
	return count;
}
