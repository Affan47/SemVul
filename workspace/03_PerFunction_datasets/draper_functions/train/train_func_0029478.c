gsi_replace_with_seq (gimple_stmt_iterator *gsi, gimple_seq seq,
		      bool update_eh_info)
{
  gimple_stmt_iterator seqi;
  gimple last;
  if (gimple_seq_empty_p (seq))
    {
      gsi_remove (gsi, true);
      return;
    }
  seqi = gsi_last (seq);
  last = gsi_stmt (seqi);
  gsi_remove (&seqi, false);
  gsi_insert_seq_before (gsi, seq, GSI_SAME_STMT);
  gsi_replace (gsi, last, update_eh_info);
}
