load_old_file (char *fname)
{
  FILE        *f;
  GtkTreeIter  parent;
  GtkTreeIter  iter;

  gtk_tree_model_get_iter_first (mm_model, &parent);

  f = fopen (fname, "r");
  if (f)
  {
    int depth = 0;

    for (;;)
    {
      char *id = read_line (f);
      if (!id)
	break;

      if (!strncmp (id, "<sub>", 5))
      {
	gtk_tree_store_append (mm_store, &iter, depth ? &parent : NULL);
	gtk_tree_store_set (mm_store, &iter, COLUMN_TITLE, &id[5], -1);

	parent = iter;
	depth++;
      }
      else if (!strncmp (id, "</sub>", 6))
      {

	gtk_tree_model_iter_parent (mm_model,
				    &iter, &parent);
	if (--depth < 0)
	{
	  g_printerr (_("mediamarks: media marks file %s corrupted - ignoring rest of file\n"),
		   fname);
	  free (id);
	  return;
	}
	parent = iter;
      }
      else
      {
	play_item_t *play_item;
	char        *mrl, *str;
	int          time = 0;

	mrl = read_line (f);
	if (!mrl)
	{
	  free (id);
	  break;
	}

	str = read_line (f);
	if (!str)
	{
	  free (mrl);
	  free (id);
	  break;
	}

	sscanf (str, "%d", &time);
	play_item = play_item_new (id, mrl, time, 0);

	gtk_tree_store_append (mm_store, &iter, depth ? &parent : NULL);
	gtk_tree_store_set (mm_store, &iter,
			    COLUMN_TITLE, id,
			    COLUMN_MRL, mrl,
			    COLUMN_PLAY_ITEM, play_item,
			    -1);

	free (str);
	free (mrl);
      }


      free (id);
      id = read_line (f);
      if (!id)
	break;
      free (id);
    }
    fclose (f);
  }
  else
    g_printerr (_("mediamarks: load failed!\n"));
}
