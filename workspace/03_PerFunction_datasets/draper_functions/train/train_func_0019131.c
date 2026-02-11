cups_copy_media_db(
    _cups_media_db_t *mdb)
{
  _cups_media_db_t *temp;


  if ((temp = calloc(1, sizeof(_cups_media_db_t))) == NULL)
    return (NULL);

  if (mdb->color)
    temp->color = _cupsStrAlloc(mdb->color);
  if (mdb->key)
    temp->key = _cupsStrAlloc(mdb->key);
  if (mdb->info)
    temp->info = _cupsStrAlloc(mdb->info);
  if (mdb->size_name)
    temp->size_name = _cupsStrAlloc(mdb->size_name);
  if (mdb->source)
    temp->source = _cupsStrAlloc(mdb->source);
  if (mdb->type)
    temp->type = _cupsStrAlloc(mdb->type);

  temp->width  = mdb->width;
  temp->length = mdb->length;
  temp->bottom = mdb->bottom;
  temp->left   = mdb->left;
  temp->right  = mdb->right;
  temp->top    = mdb->top;

  return (temp);
}
