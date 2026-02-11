maybe_record_in_goto_queue (struct leh_state *state, gimple stmt)
{
  struct leh_tf_state *tf = state->tf;
  treemple new_stmt;

  if (!tf)
    return;

  switch (gimple_code (stmt))
    {
    case GIMPLE_COND:
      new_stmt.tp = gimple_op_ptr (stmt, 2);
      record_in_goto_queue_label (tf, new_stmt, gimple_cond_true_label (stmt));
      new_stmt.tp = gimple_op_ptr (stmt, 3);
      record_in_goto_queue_label (tf, new_stmt, gimple_cond_false_label (stmt));
      break;
    case GIMPLE_GOTO:
      new_stmt.g = stmt;
      record_in_goto_queue_label (tf, new_stmt, gimple_goto_dest (stmt));
      break;

    case GIMPLE_RETURN:
      tf->may_return = true;
      new_stmt.g = stmt;
      record_in_goto_queue (tf, new_stmt, -1, false);
      break;

    default:
      gcc_unreachable ();
    }
}
