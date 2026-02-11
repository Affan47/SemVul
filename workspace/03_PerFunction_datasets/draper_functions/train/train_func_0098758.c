photos_query_builder_where (gboolean global, gint flags)
{
  PhotosBaseManager *col_mngr;
  PhotosBaseManager *srch_typ_mngr;
  gchar *col_mngr_where = NULL;
  gchar *filter = NULL;
  gchar *optional = NULL;
  gchar *sparql;
  gchar *srch_typ_mngr_where = NULL;

  col_mngr = photos_collection_manager_dup_singleton ();

  srch_typ_mngr = photos_search_type_manager_dup_singleton ();
  photos_query_builder_set_search_type (flags);
  srch_typ_mngr_where = photos_search_type_manager_get_where (PHOTOS_SEARCH_TYPE_MANAGER (srch_typ_mngr));

  optional = photos_query_builder_optional ();

  if (!(flags & PHOTOS_QUERY_FLAGS_UNFILTERED))
    {
      if (global)
        {


          col_mngr_where = photos_collection_manager_get_where (PHOTOS_COLLECTION_MANAGER (col_mngr));
        }

      filter = photos_query_builder_filter (flags);
    }

  sparql = g_strdup_printf ("WHERE { %s %s %s %s }",
                            srch_typ_mngr_where,
                            optional,
                            (col_mngr_where != NULL) ? col_mngr_where : "",
                            (filter != NULL) ? filter : "");

  photos_query_builder_set_search_type (PHOTOS_QUERY_FLAGS_NONE);
  g_free (col_mngr_where);
  g_free (filter);
  g_free (srch_typ_mngr_where);
  g_object_unref (col_mngr);
  g_object_unref (srch_typ_mngr);

  return sparql;
}
