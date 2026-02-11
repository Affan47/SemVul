meta_changed_cb (G_GNUC_UNUSED GdaMetaStore *store, GSList *changes, HubConnection *hc)
{
	GSList *list;
	for (list = changes; list; list = list->next) {
		GdaMetaStoreChange *ch = (GdaMetaStoreChange*) list->data;
		GValue *tsn, *tn;


		if (!strcmp (ch->table_name, "_tables")) {
			switch (ch->c_type) {
			case GDA_META_STORE_ADD: {

				tsn = g_hash_table_lookup (ch->keys, "+6");
				tn = g_hash_table_lookup (ch->keys, "+2");
				if (tn && tsn && !gda_value_compare (tsn, tn))
					table_add (hc, tn, NULL);
				break;
			}
			case GDA_META_STORE_REMOVE: {

				tsn = g_hash_table_lookup (ch->keys, "-6");
				tn = g_hash_table_lookup (ch->keys, "-2");
				if (tn && tsn && !gda_value_compare (tsn, tn))
					table_remove (hc, tn);
				break;
			}
			case GDA_META_STORE_MODIFY: {

				tsn = g_hash_table_lookup (ch->keys, "-6");
				tn = g_hash_table_lookup (ch->keys, "-2");
				if (tn && tsn && !gda_value_compare (tsn, tn))
					table_remove (hc, tn);
				tsn = g_hash_table_lookup (ch->keys, "+6");
				tn = g_hash_table_lookup (ch->keys, "+2");
				if (tn && tsn && !gda_value_compare (tsn, tn))
					table_add (hc, tn, NULL);
				break;
			}
			}
		}
		else if (!strcmp (ch->table_name, "_columns")) {

		}
	}
}
