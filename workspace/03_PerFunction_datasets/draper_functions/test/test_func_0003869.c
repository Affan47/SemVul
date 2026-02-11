record_in_goto_queue_label (struct leh_tf_state *tf, treemple stmt, tree label,
			    location_t location)
{
  int index;
  treemple temp, new_stmt;

  if (!label)
    return;


  if (TREE_CODE (label) != LABEL_DECL)
    return;


  temp.t = label;
  if (!outside_finally_tree (temp, tf->try_finally_expr))
    return;

  if (! tf->dest_array.exists ())
    {
      tf->dest_array.create (10);
      tf->dest_array.quick_push (label);
      index = 0;
    }
  else
    {
      int n = tf->dest_array.length ();
      for (index = 0; index < n; ++index)
        if (tf->dest_array[index] == label)
          break;
      if (index == n)
        tf->dest_array.safe_push (label);
    }


  new_stmt = stmt;
  record_in_goto_queue (tf, new_stmt, index, true, location);
}
