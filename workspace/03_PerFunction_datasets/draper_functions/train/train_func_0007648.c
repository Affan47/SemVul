SaveZones(GtkWidget *w, gpointer clocklist)
{
  FILE *cf;
  extern GString *configfile;
  extern gint changed;
  gint N,i;
  gchar *description, *timezone;
  GtkTreeModel *clocklistModel;
  GtkTreeIter iter;
  gboolean gotIter = FALSE;

  if ( !(cf=fopen(configfile->str,"w")) ) {
    return 0;
  }

  clocklistModel = gtk_tree_view_get_model( clocklist );
  gotIter =  gtk_tree_model_get_iter_first(clocklistModel, &iter);

  while( gotIter )
  {
     gtk_tree_model_get( clocklistModel, &iter,
			 TZ_NAME, &timezone,
			 TZ_DESCRIPTION, &description,
			 -1);


    if(strlen(description)==0)
      fprintf(cf,"%s\n", timezone );
    else
       fprintf(cf,"%s    \"%s\"\n", timezone, description );

    g_free(timezone);
    g_free(description);
    gotIter = gtk_tree_model_iter_next( clocklistModel, &iter );
  }

  changed=0;
  return ( ! fclose( cf ) );
}
