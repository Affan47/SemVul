gth_seq_con_get_tran_seq_rc(GthSeqCon *seq_con, unsigned long seq_num)
{
  gt_assert(seq_con && seq_con->c_class && seq_con->c_class->get_tran_seq_rc);
  return seq_con->c_class->get_tran_seq_rc(seq_con, seq_num);
}
