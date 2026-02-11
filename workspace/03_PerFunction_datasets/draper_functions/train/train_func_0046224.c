lower_cleanup (struct leh_state *state, gimple tp)
{
  struct leh_state this_state = *state;
  eh_region this_region = NULL;
  struct leh_tf_state fake_tf;
  gimple_seq result;
  bool cleanup_dead = cleanup_is_dead_in (state->cur_region);

  if (flag_exceptions && !cleanup_dead)
    {
      this_region = gen_eh_region_cleanup (state->cur_region);
      this_state.cur_region = this_region;
    }

  lower_eh_constructs_1 (&this_state, gimple_try_eval (tp));

  if (cleanup_dead || !eh_region_may_contain_throw (this_region))
    return gimple_try_eval (tp);


  memset (&fake_tf, 0, sizeof (fake_tf));
  fake_tf.top_p = fake_tf.try_finally_expr = tp;
  fake_tf.outer = state;
  fake_tf.region = this_region;
  fake_tf.may_fallthru = gimple_seq_may_fallthru (gimple_try_eval (tp));
  fake_tf.may_throw = true;

  honor_protect_cleanup_actions (state, NULL, &fake_tf);

  if (fake_tf.may_throw)
    {


      lower_eh_constructs_1 (state, gimple_try_cleanup (tp));
      result = frob_into_branch_around (tp, this_region,
                                        fake_tf.fallthru_label);
    }
  else
    {


      result = gimple_try_eval (tp);
      if (fake_tf.fallthru_label)
	{
	  gimple x = gimple_build_label (fake_tf.fallthru_label);
	  gimple_seq_add_stmt (&result, x);
	}
    }
  return result;
}
