lower_try_finally_onedest (struct leh_state *state, struct leh_tf_state *tf)
{
  struct goto_queue_node *q, *qe;
  gimple x;
  gimple_seq finally;
  tree finally_label;
  location_t loc = gimple_location (tf->try_finally_expr);

  finally = gimple_try_cleanup (tf->top_p);
  tf->top_p_seq = gimple_try_eval (tf->top_p);

  lower_eh_constructs_1 (state, finally);

  if (tf->may_throw)
    {


      emit_post_landing_pad (&eh_seq, tf->region);
      gimple_seq_add_seq (&eh_seq, finally);
      emit_resx (&eh_seq, tf->region);
      return;
    }

  if (tf->may_fallthru)
    {


      gimple_seq_add_seq (&tf->top_p_seq, finally);
      return;
    }

  finally_label = create_artificial_label (loc);
  x = gimple_build_label (finally_label);
  gimple_seq_add_stmt (&tf->top_p_seq, x);

  gimple_seq_add_seq (&tf->top_p_seq, finally);

  q = tf->goto_queue;
  qe = q + tf->goto_queue_active;

  if (tf->may_return)
    {

      tree return_val = NULL;
      for (; q < qe; ++q)
	do_return_redirection (q, finally_label, NULL, &return_val);
      replace_goto_queue (tf);
    }
  else
    {

      for (; q < qe; ++q)
	do_goto_redirection (q, finally_label, NULL, tf);
      replace_goto_queue (tf);

      if (VEC_index (tree, tf->dest_array, 0) == tf->fallthru_label)
	{


	  tf->fallthru_label = NULL;
	  return;
	}
    }


  x = tf->goto_queue[0].cont_stmt;
  gimple_seq_add_stmt (&tf->top_p_seq, x);
  maybe_record_in_goto_queue (state, x);
}
