read_rk_result(struct anthy_input_context* ictx)
{
  int ret;

  ret = rk_result(ictx->rkctx, ictx->hbuf + ictx->n_hbuf,
		  ictx->s_hbuf - ictx->n_hbuf);
  if (ret > 0) {
    if (ictx->s_hbuf - ictx->n_hbuf > 0)
      ictx->n_hbuf = ictx->s_hbuf - 1;

    ensure_buffer(&ictx->hbuf, &ictx->s_hbuf, ictx->n_hbuf + ret + 1);

    rk_result(ictx->rkctx, ictx->hbuf + ictx->n_hbuf,
	      ictx->s_hbuf - ictx->n_hbuf);
  }
  if (ictx->hbuf)
    ictx->n_hbuf += strlen(ictx->hbuf + ictx->n_hbuf);
}
