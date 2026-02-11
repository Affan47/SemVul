remove_unreachable_alias_pairs (void)
{
  symbol_alias_set_t *visible;
  unsigned i;
  alias_pair *p;

  if (alias_pairs == NULL)
    return;


  visible = propagate_aliases_forward (trivially_visible_alias, NULL);

  for (i = 0; VEC_iterate (alias_pair, alias_pairs, i, p); )
    {
      if (!DECL_EXTERNAL (p->decl)
	  && !symbol_alias_set_contains (visible, p->decl))
	{
	  VEC_unordered_remove (alias_pair, alias_pairs, i);
	  continue;
	}

      i++;
    }

  symbol_alias_set_destroy (visible);
}
