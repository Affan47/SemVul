iclass_check_param (pixma_t * s, pixma_scan_param_t * sp)
{
  UNUSED (s);

  sp->depth = 8;
  sp->line_size = ALIGN_SUP (sp->w, 32) * sp->channels;


  if (sp->source == PIXMA_SOURCE_FLATBED
      && ( s->cfg->pid == MF4770_PID ))
    sp->h = MIN (sp->h, 877 * sp->xdpi / 75);

  return 0;
}
