accepted (enum accept_stat acpt_stat,
	  struct rpc_err *error)
{
  switch (acpt_stat)
    {

    case PROG_UNAVAIL:
      error->re_status = RPC_PROGUNAVAIL;
      return;

    case PROG_MISMATCH:
      error->re_status = RPC_PROGVERSMISMATCH;
      return;

    case PROC_UNAVAIL:
      error->re_status = RPC_PROCUNAVAIL;
      return;

    case GARBAGE_ARGS:
      error->re_status = RPC_CANTDECODEARGS;
      return;

    case SYSTEM_ERR:
      error->re_status = RPC_SYSTEMERROR;
      return;

    case SUCCESS:
      error->re_status = RPC_SUCCESS;
      return;
    }

  error->re_status = RPC_FAILED;
  error->re_lb.s1 = (long) MSG_ACCEPTED;
  error->re_lb.s2 = (long) acpt_stat;
}
