expmem_dupwait(void *x)
{
  register struct dupwait_info *p = (struct dupwait_info *) x;
  int tot = sizeof(struct dupwait_info);

  if (p && p->chat && DCC_CHAT.expmem)
    tot += DCC_CHAT.expmem(p->chat);
  return tot;
}
