game_position_solve_impl (ExactSolution *const result,
                          const GamePosition  *const gp,
                          const int achievable,
                          const int cutoff,
                          PVCell ***pve_parent_line_p)
{
  result->node_count++;
  SearchNode *node  = NULL;
  SearchNode *node2 = NULL;
  PVCell **pve_line = NULL;

  if (log_env->log_is_on) {
    call_count++;
    gp_hash_stack_fill_point++;
    LogDataH log_data;
    log_data.sub_run_id = 0;
    log_data.call_id = call_count;
    log_data.hash = game_position_hash(gp);
    gp_hash_stack[gp_hash_stack_fill_point] = log_data.hash;
    log_data.parent_hash = gp_hash_stack[gp_hash_stack_fill_point - 1];
    log_data.blacks = (gp->board)->blacks;
    log_data.whites = (gp->board)->whites;
    log_data.player = gp->player;
    gchar *json_doc = game_tree_log_data_h_json_doc(gp_hash_stack_fill_point, gp);
    log_data.json_doc = json_doc;
    game_tree_log_write_h(log_env, &log_data);
    g_free(json_doc);
  }

  const SquareSet moves = game_position_legal_moves(gp);
  if (0ULL == moves) {
    pve_line = pve_line_create(pve);
    GamePosition *flipped_players = game_position_pass(gp);
    if (game_position_has_any_legal_move(flipped_players)) {
      node = search_node_negated(game_position_solve_impl(result, flipped_players, -cutoff, -achievable, &pve_line));
    } else {
      result->leaf_count++;
      node = search_node_new(pass_move, game_position_final_value(gp));
    }
    pve_line_add_move(pve, pve_line, pass_move);
    pve_line_delete(pve, *pve_parent_line_p);
    *pve_parent_line_p = pve_line;
    game_position_free(flipped_players);
  } else {
    MoveList move_list;
    move_list_init(&move_list);
    sort_moves_by_mobility_count(&move_list, gp);
    for (MoveListElement *element = move_list.head.succ; element != &move_list.tail; element = element->succ) {
      const Square move = element->sq;
      if (!node) node = search_node_new(move, achievable);
      GamePosition *gp2 = game_position_make_move(gp, move);
      pve_line = pve_line_create(pve);
      node2 = search_node_negated(game_position_solve_impl(result, gp2, -cutoff, -node->value, &pve_line));
      game_position_free(gp2);
      if (node2->value > node->value) {
        search_node_free(node);
        node = node2;
        node->move = move;
        node2 = NULL;
        pve_line_add_move(pve, pve_line, move);
        pve_line_delete(pve, *pve_parent_line_p);
        *pve_parent_line_p = pve_line;
        if (node->value >= cutoff) goto out;
      } else {
        search_node_free(node2);
        pve_line_delete(pve, pve_line);
      }
    }
  }
 out:
  if (log_env->log_is_on) {
    gp_hash_stack_fill_point--;
  }
  return node;
}
