of_SET_WORDR(vthread_t thr, vvp_code_t cp)
{

      vvp_net_ptr_t ptr (cp->net, 0);

      vvp_send_real(ptr, thr->words[cp->bit_idx[0]].w_real, thr->wt_context);

      return true;
}
