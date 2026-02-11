mc_update_move_values(struct mc_board *mc)
{
  int pos;
  int partition;
  for (pos = mc->queue[0]; pos != 1; pos = mc->queue[pos]) {
    partition = pos & (NUM_MOVE_PARTITIONS - 1);
    if ((mc->board[pos] != EMPTY || mc_is_suicide(mc, pos, WHITE))) {
      if (mc->move_partition_lists_white[pos] != 0) {
	mc_remove_move(pos, partition, mc->move_values_white,
		       mc->move_partition_lists_white,
		       mc->partitioned_move_value_sums_white,
		       &mc->move_value_sum_white);
      }
    }
    else {
      if (mc->move_partition_lists_white[pos] == 0)
	mc_add_move(mc, pos, WHITE, partition, mc->move_values_white,
		    mc->move_partition_lists_white,
		    mc->partitioned_move_value_sums_white,
		    &mc->move_value_sum_white);
      else
	mc_update_move(mc, pos, WHITE, partition, mc->move_values_white,
		       mc->partitioned_move_value_sums_white,
		       &mc->move_value_sum_white);
    }

    if ((mc->board[pos] != EMPTY || mc_is_suicide(mc, pos, BLACK))) {
      if (mc->move_partition_lists_black[pos] != 0) {
	mc_remove_move(pos, partition, mc->move_values_black,
		       mc->move_partition_lists_black,
		       mc->partitioned_move_value_sums_black,
		       &mc->move_value_sum_black);
      }
    }
    else {
      if (mc->move_partition_lists_black[pos] == 0)
	mc_add_move(mc, pos, BLACK, partition, mc->move_values_black,
		    mc->move_partition_lists_black,
		    mc->partitioned_move_value_sums_black,
		    &mc->move_value_sum_black);
      else
	mc_update_move(mc, pos, BLACK, partition, mc->move_values_black,
		       mc->partitioned_move_value_sums_black,
		       &mc->move_value_sum_black);
    }
  }
}
