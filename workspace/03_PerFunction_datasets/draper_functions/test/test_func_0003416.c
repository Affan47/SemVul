add_to_dominance_info (enum cdi_direction dir, basic_block bb)
{
  if (!dom_computed[dir])
    abort ();

  if (bb->dom[dir])
    abort ();

  bb->dom[dir] = et_new_tree (bb);

  if (dom_computed[dir] == DOM_OK)
    dom_computed[dir] = DOM_NO_FAST_QUERY;
}
