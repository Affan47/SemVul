pve_line_create (PVEnv *pve)
{
  g_assert(pve_verify_consistency(pve, NULL, NULL));
  PVCell **line_p = *(pve->lines_stack_head);
  *(line_p) = NULL;
  pve->lines_stack_head++;
  return line_p;
}
