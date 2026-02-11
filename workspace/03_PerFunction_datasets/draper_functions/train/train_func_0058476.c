compute_FOLLOWS (void)
{
  goto_number i;

  relation_digraph (includes, ngotos, &goto_follows);

  for (i = 0; i < ngotos; i++)
    free (includes[i]);

  free (includes);
}
