standard_iv_increment_position (struct loop *loop, gimple_stmt_iterator *bsi,
				bool *insert_after)
{
  basic_block bb = ip_normal_pos (loop), latch = ip_end_pos (loop);
  gimple last = last_stmt (latch);

  if (!bb
      || (last && gimple_code (last) != GIMPLE_LABEL))
    {
      *bsi = gsi_last_bb (latch);
      *insert_after = true;
    }
  else
    {
      *bsi = gsi_last_bb (bb);
      *insert_after = false;
    }
}
