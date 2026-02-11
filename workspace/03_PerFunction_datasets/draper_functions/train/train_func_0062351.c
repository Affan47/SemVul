lib_cmd_take_all (sc_gameref_t game)
{
  const sc_filterref_t filter = gs_get_filter (game);
  sc_int objects;


  gs_set_multiple_references (game);
  objects = lib_apply_multiple_filter (game,
                                       lib_take_not_associated_filter, -1,
                                       NULL);
  gs_clear_multiple_references (game);
  if (objects > 0)
    lib_take_backend (game);
  else
    pf_buffer_string (filter, "There is nothing to pick up here.");

  pf_buffer_character (filter, '\n');
  return TRUE;
}
