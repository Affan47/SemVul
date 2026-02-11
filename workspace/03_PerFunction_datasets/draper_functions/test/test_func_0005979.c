CodeInList(gchar *code, GSList *List)
{


  GSList *item;

  item = List;
  while (item) {
    if ( ! strcmp(code,((NameCodeType *)item->data)->code) )
      return TRUE;
    item = item->next;
  }
  return FALSE;
}
