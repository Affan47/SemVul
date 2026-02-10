gather_blocks_in_sese_region (basic_block entry, basic_block exit,
			      vec<basic_block> *bbs_p)
{
  basic_block son;

  for (son = first_dom_son (CDI_DOMINATORS, entry);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    {
      bbs_p->safe_push (son);
      if (son != exit)
	gather_blocks_in_sese_region (son, exit, bbs_p);
    }
}
