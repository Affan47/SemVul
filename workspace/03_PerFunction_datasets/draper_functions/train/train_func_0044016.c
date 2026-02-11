lam_ssi_rpi_sysv_buffer(struct lam_ssi_rpi_proc *ps)
{
  struct lam_ssi_rpi_cbuf_msg msg;
  int len;


  LAM_ZERO_ME(msg);
  msg.cm_env = ps->cp_inbox->pb_header.bh_env;
  len = LAM_min(msg.cm_env.ce_len, lam_ssi_rpi_sysv_short);

  if (len > 0) {


    msg.cm_buf = (char *) malloc(len);
    if (msg.cm_buf == 0)
      return (LAMERROR);

    lam_memcpy(msg.cm_buf, ps->cp_inbox + 1, len);
  } else {
    msg.cm_buf = 0;
  }

  if (lam_ssi_rpi_sysv_readunlock(ps))
    return (LAMERROR);
  ps->cp_locked = 0;

  msg.cm_proc = 0;
  msg.cm_req = 0;
  msg.cm_dont_delete = 0;
  return (lam_ssi_rpi_cbuf_append(&msg) ? 0 : LAMERROR);
}
