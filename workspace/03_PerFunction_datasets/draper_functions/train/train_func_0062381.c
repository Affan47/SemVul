_dup (FolksSmallSet *self,
    guint i)
{
  if (self->item_dup == NULL)
    return (gpointer) _get (self, i);

  return self->item_dup ((gpointer) _get (self, i));
}
