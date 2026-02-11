construct_piece_list (rtx loc_note, HOST_WIDE_INT bitpos,
		      HOST_WIDE_INT bitsize)
{
  if (bitsize != -1)
    {
      loc_note = decl_piece_node (loc_note, bitsize, NULL_RTX);
      if (bitpos != 0)
	loc_note = decl_piece_node (NULL_RTX, bitpos, loc_note);
    }
  return loc_note;
}
