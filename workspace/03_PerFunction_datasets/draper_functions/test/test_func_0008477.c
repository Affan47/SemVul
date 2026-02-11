Close_DB(HITS_DB *db)
{ HITS_TRACK *t, *p;

  if (db->loaded)
    free(((char *) (db->bases)) - 1);
  else if (db->bases != NULL)
    fclose((FILE *) db->bases);
  free(db->reads-1);
  free(db->path);

  Close_QVs(db);

  for (t = db->tracks; t != NULL; t = p)
    { p = t->next;
      free(t->anno);
      free(t->data);
      free(t);
    }
}
