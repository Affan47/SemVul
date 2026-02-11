router_my_exit_policy_is_reject_star(void)
{
  if (!router_get_my_routerinfo())
    return -1;

  return desc_routerinfo->policy_is_reject_star;
}
