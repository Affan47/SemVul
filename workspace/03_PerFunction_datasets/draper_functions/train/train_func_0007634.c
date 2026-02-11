release_armor_context (armor_filter_context_t *afx)
{
  if (!afx)
    return;


  if (!afx->refcount)
    return;

  if ( --afx->refcount )
    return;
  xfree (afx);
}
