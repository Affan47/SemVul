reinitialize_databases (void)
{
  GList *engines = NULL, *engine;
  GList *cnxns, *l;
  GConfEngine *conf;

  if (engines_by_db)
    g_hash_table_foreach (engines_by_db,
			  engines_by_db_get_all_func,
			  &engines);


  for (engine = engines; engine; engine = engine->next)
    {
      conf = engine->data;

      g_hash_table_remove (engines_by_db, conf->database);
      ensure_database (conf, FALSE, NULL);
    }


  for (engine = engines; engine; engine = engine->next)
    {
      conf = engine->data;

      cnxns = NULL;
      g_hash_table_foreach (conf->notify_ids,
			    cnxn_get_all_func,
			    &cnxns);

      for (l = cnxns; l; l = l->next)
	{
	  GConfCnxn *cnxn = l->data;

	  send_notify_add (conf, cnxn, NULL);
	}

      g_list_free (cnxns);
    }

  g_list_free (engines);
}
