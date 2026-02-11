set_hover_state(struct unit_list *punits, enum cursor_hover_state state,
		     enum unit_activity activity,
		     enum unit_orders order)
{
  fc_assert_ret((punits && unit_list_size(punits) > 0)
                || state == HOVER_NONE);
  fc_assert_ret(state == HOVER_CONNECT || activity == ACTIVITY_LAST);
  fc_assert_ret(state == HOVER_GOTO || order == ORDER_LAST);
  hover_state = state;
  connect_activity = activity;
  goto_last_order = order;
  exit_goto_state();
}
