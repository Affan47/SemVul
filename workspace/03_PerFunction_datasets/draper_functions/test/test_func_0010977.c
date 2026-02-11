insert_attribute_hash(gchar *attr)
{
  PerlPluginTimedSList *tl;
  gchar *indexfile;
  struct stat filestat;


  if((tl = g_hash_table_lookup(attribute_hash,attr)) != NULL) {
    gpointer origkey;
    gpointer value;
    g_hash_table_lookup_extended(attribute_hash,attr,&origkey,&value);
    g_hash_table_remove(attribute_hash,origkey);
    free_attribute_hash_key(origkey,value,NULL);
    debug_print("Existing key `%s' freed.\n",attr);
  }

  tl = g_new0(PerlPluginTimedSList,1);
  tl->g_slist = NULL;

  attribute_key = g_strdup(attr);
  g_hash_table_insert(attribute_hash,attribute_key,tl);

  addrindex_load_person_attribute(attribute_key,add_to_attribute_hash);

  indexfile = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, ADDRESSBOOK_INDEX_FILE, NULL);
  if(stat(indexfile,&filestat) == 0)
    tl->mtime = filestat.st_mtime;
  g_free(indexfile);

  debug_print("added key `%s' to attribute_hash\n",attribute_key?attribute_key:"");
}
