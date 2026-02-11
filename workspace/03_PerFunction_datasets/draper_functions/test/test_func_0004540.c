tile_type_get(const struct cm_state *state,
						int type)
{

  fc_assert_ret_val(0 <= type, NULL);
  fc_assert_ret_val(state->lattice.size > type, NULL);
  return state->lattice.p[type];
}
