df_chain_copy (df_ref to_ref,
	       struct df_link *from_ref)
{
  while (from_ref)
    {
      df_chain_create (to_ref, from_ref->ref);
      from_ref = from_ref->next;
    }
}
