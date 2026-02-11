get_attribute_value(gchar *email, gchar *attr, gchar *bookname)
{
  GSList *walk;
  PerlPluginTimedSList *tl;


  if(attribute_hash == NULL) {
    attribute_hash = g_hash_table_new(g_str_hash,g_str_equal);
    debug_print("attribute_hash created\n");
  }

  if(update_attribute_hash(attr)) {
    debug_print("Initialisation of attribute hash entry `%s' is necessary\n",attr);
    insert_attribute_hash(attr);
  }

  if((tl = (PerlPluginTimedSList*) g_hash_table_lookup(attribute_hash,attr)) == NULL)
    return NULL;

  walk = tl->g_slist;
  for(; walk != NULL; walk = g_slist_next(walk)) {
    PerlPluginAttributeEntry *ae = (PerlPluginAttributeEntry *) walk->data;
    gchar *a, *b;
    a = g_utf8_strdown(ae->address, -1);
    b = g_utf8_strdown(email, -1);
    if(!g_utf8_collate(a, b)) {
      if((bookname == NULL) ||
   ((ae->bookname != NULL) && !strcmp(bookname,ae->bookname))) {
        g_free(a); g_free(b);
  return ae->value;
      }
    }
    g_free(a); g_free(b);
  }
  return NULL;
}
