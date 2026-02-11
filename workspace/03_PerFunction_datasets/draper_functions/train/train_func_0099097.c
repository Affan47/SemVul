insert_metainfo(char *key, char *value)
{
	MetaInfo *mi;
	MetaInfo *mi_new;

	for (mi = mi_store; mi; mi = mi->next)
	{
		if (StrEquals(mi->key, key))
		{


			free (mi->value);
			CopyString(&mi->value, value);

			return;
		}
	}


	mi_new = new_metainfo();
	mi_new->key = key;
	CopyString(&mi_new->value, value);

	mi_new->next = mi_store;
	mi_store = mi_new;

	return;
}
