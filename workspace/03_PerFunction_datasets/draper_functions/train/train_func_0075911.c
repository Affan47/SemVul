identify(int sig)
{
  if (ID_next && ID_next->i_flags&I_NEED_ID) {
    xmit_id(ID_next);
    ID_next = NULL;
    sked_id(NULL);
    signal(sig,identify);
  }
}
