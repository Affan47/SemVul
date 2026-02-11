uip_match_text (sc_ptnoderef_t node)
{
  const sc_gameref_t game = uip_get_game ();
  const sc_var_setref_t vars = gs_get_vars (game);
  sc_int start_posn, limit, index_;
  sc_bool matched;
  sc_ptnoderef_t list;


  start_posn = uip_posn;


  list = uip_new_node (NODE_LIST);
  list->left_child = node->right_sibling;


  matched = FALSE;
  limit = strlen (uip_string) + 1;
  for (index_ = uip_posn + 1; index_ < limit; index_++)
    {
      uip_posn = index_;
      if (uip_match_node (list))
        {

          uip_posn = index_;
          matched = TRUE;
          break;
        }
    }


  uip_destroy_node (list);


  if (matched)
    {
      sc_char *string;


      string = sc_malloc (uip_posn - start_posn + 1);
      memcpy (string, uip_string + start_posn, uip_posn - start_posn);
      string[uip_posn - start_posn] = NUL;


      for (index_ = 0; string[index_] != NUL; index_++)
        string[index_] = sc_tolower (string[index_]);
      var_set_ref_text (vars, string);
      sc_free (string);


      return TRUE;
    }
  else
    {

      uip_posn = start_posn;


      return FALSE;
    }
}
