transaction_splits_parse(Transaction *ope, gchar *cats, gchar *amounts, gchar *memos)
{
gchar **cat_a, **amt_a, **mem_a;
guint count, i;
guint32 kcat;
gdouble amount;
Split *split;

	DB( g_print(" split parse %s :: %s :: %s\n", cats, amounts, memos) );

	cat_a = g_strsplit (cats, "||", 0);
	amt_a = g_strsplit (amounts, "||", 0);
	mem_a = g_strsplit (memos, "||", 0);

	count = g_strv_length(amt_a);
	if( (count == g_strv_length(cat_a)) && (count == g_strv_length(mem_a)) )
	{
		for(i=0;i<count;i++)
		{
			kcat = atoi(cat_a[i]);
			amount = g_ascii_strtod(amt_a[i], NULL);
			split = da_split_new(kcat, amount, mem_a[i]);
			da_transaction_splits_append (ope, split);
		}

		ope->flags |= OF_SPLIT;
	}
	else
	{
		g_warning("invalid split parse");
	}

	g_strfreev (mem_a);
	g_strfreev (amt_a);
	g_strfreev (cat_a);

	return count;
}
