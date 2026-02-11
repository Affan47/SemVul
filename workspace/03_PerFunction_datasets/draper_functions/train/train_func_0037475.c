gimple_set_bb (gimple stmt, basic_block bb)
{
  stmt->gsbase.bb = bb;


  if (cfun->cfg && gimple_code (stmt) == GIMPLE_LABEL)
    {
      tree t;
      int uid;

      t = gimple_label_label (stmt);
      uid = LABEL_DECL_UID (t);
      if (uid == -1)
	{
	  unsigned old_len = vec_safe_length (label_to_block_map);
	  LABEL_DECL_UID (t) = uid = cfun->cfg->last_label_uid++;
	  if (old_len <= (unsigned) uid)
	    {
	      unsigned new_len = 3 * uid / 2 + 1;

	      vec_safe_grow_cleared (label_to_block_map, new_len);
	    }
	}

      (*label_to_block_map)[uid] = bb;
    }
}
