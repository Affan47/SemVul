sig_waiting_conn_free (SigWaitingConn *sig)
{
  g_assert (sig != NULL);

  tp_g_value_slice_free (sig->param);
  g_slice_free (SigWaitingConn, sig);
}
