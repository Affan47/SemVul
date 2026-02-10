next_conversion (conversion *conv)
{
  if (conv == NULL
      || conv->kind == ck_identity
      || conv->kind == ck_ambig
      || conv->kind == ck_list)
    return NULL;
  return conv->u.next;
}
