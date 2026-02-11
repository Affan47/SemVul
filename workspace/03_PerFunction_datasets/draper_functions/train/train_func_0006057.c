lto_input_eh_catch_list (struct lto_input_block *ib, struct data_in *data_in,
			 eh_catch *last_p)
{
  eh_catch first;
  enum LTO_tags tag;

  *last_p = first = NULL;
  tag = streamer_read_record_start (ib);
  while (tag)
    {
      tree list;
      eh_catch n;

      lto_tag_check_range (tag, LTO_eh_catch, LTO_eh_catch);


      n = ggc_alloc_cleared_eh_catch_d ();
      n->type_list = stream_read_tree (ib, data_in);
      n->filter_list = stream_read_tree (ib, data_in);
      n->label = stream_read_tree (ib, data_in);


      for (list = n->filter_list; list; list = TREE_CHAIN (list))
	add_type_for_runtime (TREE_VALUE (list));


      if (*last_p)
	(*last_p)->next_catch = n;
      n->prev_catch = *last_p;
      *last_p = n;


      if (first == NULL)
	first = n;

      tag = streamer_read_record_start (ib);
    }

  return first;
}
