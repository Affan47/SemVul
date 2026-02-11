_wnck_pager_get_workspace_name (WnckPager *pager,
                                int        i)
{
  WnckWorkspace *space;

  space = wnck_screen_get_workspace (pager->priv->screen, i);
  if (space)
    return wnck_workspace_get_name (space);
  else
    return NULL;
}
