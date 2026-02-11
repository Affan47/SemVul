compare_type_names(CHARSET_INFO *charset, TYPELIB *t1, TYPELIB *t2)
{
  for (uint i= 0; i < t1->count; i++)
    if (my_strnncoll(charset,
                     (const uchar*) t1->type_names[i],
                     t1->type_lengths[i],
                     (const uchar*) t2->type_names[i],
                     t2->type_lengths[i]))
      return FALSE;
  return TRUE;
}
