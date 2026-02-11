free_bond (struct Bond *bond)
{
  g_free (bond->text);
  g_free (bond->pango);
  g_free (bond->pango_left);
  g_free (bond->pango_right);
  if (bond->type == BOND_GROUP)
    free_bond_list (bond->group_members);
  free_orn_list (bond->ornaments[0]);
  free_orn_list (bond->ornaments[1]);
  g_free (bond);

  return;
}
