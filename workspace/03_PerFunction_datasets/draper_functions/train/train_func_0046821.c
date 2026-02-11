process_sigs (DSPAM_CTX * CTX, int age)
{
  struct _ds_storage_signature *ss;
  struct nt *del;
  struct nt_node *node;
  int delta;

  del = nt_create(NT_CHAR);
  if (del == NULL)
    return -1;

#ifdef DEBUG
    printf ("Processing sigs; age: %d\n", age);
#endif

  ss = _ds_get_nextsignature (CTX);
  while (ss != NULL)
  {
#ifdef DEBUG
    printf ("Signature: %s\n    Created: %s\n", ss->signature,
            ctime (&ss->created_on));
#endif
    delta = (((time (NULL) - ss->created_on) / 60) / 60) / 24;
    if (age == 0 || delta > age)
    {
#ifdef DEBUG
      printf ("    DELETED!\n");
#endif
      nt_add(del, ss->signature);
    }
    free(ss->data);
    free(ss);
    ss = _ds_get_nextsignature (CTX);
  }

  node = del->first;
  while(node != NULL) {
    _ds_delete_signature (CTX, node->ptr);
    node = node->next;
  }
  nt_destroy(del);

  return 0;
}
