owl_connection_defends(int move, int target1, int target2)
{
  int color = board[target1];
  int result = 0;
  int reading_nodes_when_called = get_reading_node_counter();
  int tactical_nodes;
  double start = 0.0;
  struct local_owl_data *owl;

  if (debug & DEBUG_OWL_PERFORMANCE)
    start = gg_cputime();

  ASSERT1(board[target2] == color, target2);
  TRACE("owl_connection_defends %1m %1m %1m\n", move, target1, target2);

  if (worm[target1].unconditional_status == DEAD)
    return 0;
  if (worm[target2].unconditional_status == DEAD)
    return 0;

  if (search_persistent_owl_cache(OWL_CONNECTION_DEFENDS, move, target1,
				  target2, &result, NULL, NULL, NULL))
    return result;

  init_owl(&owl, target1, target2, NO_MOVE, 1, NULL);

  if (trymove(move, color, "owl_connection_defends", target1)) {
    owl_update_goal(move, SAME_DRAGON_MAYBE_CONNECTED, NO_MOVE, owl, 0, NULL);
    if (!do_owl_attack(move, NULL, NULL, owl, 0))
      result = WIN;
    owl->lunches_are_current = 0;
    popgo();
  }
  tactical_nodes = get_reading_node_counter() - reading_nodes_when_called;

  DEBUG(DEBUG_OWL_PERFORMANCE,
	"owl_conn_defends %1m %1m %1m, result %d (%d, %d nodes, %f seconds)\n",
	move, target1, target2, result, local_owl_node_counter,
	tactical_nodes, gg_cputime() - start);

  store_persistent_owl_cache(OWL_CONNECTION_DEFENDS, move, target1, target2,
			     result, 0, 0, 0, tactical_nodes,
			     owl->goal, color);

  return result;
}
