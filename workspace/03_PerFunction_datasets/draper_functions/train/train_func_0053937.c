mail_flags_new_empty(void)
{
  struct mail_flags * flags;

  flags = malloc(sizeof(* flags));
  if (flags == NULL)
    goto err;

  flags->fl_flags = MAIL_FLAG_NEW;
  flags->fl_extension = clist_new();
  if (flags->fl_extension == NULL)
    goto free;

  return flags;

 free:
  free(flags);
 err:
  return NULL;
}
