save_macros (cpp_reader *r ATTRIBUTE_UNUSED, cpp_hashnode *h, void *data_p)
{
  struct save_macro_data *data = (struct save_macro_data *)data_p;
  if (h->type != NT_VOID
      && (h->flags & NODE_BUILTIN) == 0)
    {
      cpp_hashnode *save;
      if (data->count == ARRAY_SIZE (data->macros->macs))
	{
	  struct save_macro_item *d = data->macros;
	  data->macros = xmalloc (sizeof (struct save_macro_item));
	  data->macros->next = d;
	  data->count = 0;
	}
      save = data->macros->macs + data->count;
      data->count++;
      memcpy (save, h, sizeof (struct cpp_hashnode));
      HT_STR (&save->ident) = xmemdup (HT_STR (HT_NODE (save)),
				       HT_LEN (HT_NODE (save)),
				       HT_LEN (HT_NODE (save)) + 1);
    }
  return 1;
}
