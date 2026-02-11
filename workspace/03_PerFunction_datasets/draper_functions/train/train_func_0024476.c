debug_rli (record_layout_info rli)
{
  print_node_brief (stderr, "type", rli->t, 0);
  print_node_brief (stderr, "\noffset", rli->offset, 0);
  print_node_brief (stderr, " bitpos", rli->bitpos, 0);

  fprintf (stderr, "\naligns: rec = %u, unpack = %u, off = %u\n",
	   rli->record_align, rli->unpacked_align,
	   rli->offset_align);


  if (targetm.ms_bitfield_layout_p (rli->t))
    fprintf (stderr, "remaining in alignment = %u\n", rli->remaining_in_alignment);

  if (rli->packed_maybe_necessary)
    fprintf (stderr, "packed may be necessary\n");

  if (!VEC_empty (tree, rli->pending_statics))
    {
      fprintf (stderr, "pending statics:\n");
      debug_vec_tree (rli->pending_statics);
    }
}
