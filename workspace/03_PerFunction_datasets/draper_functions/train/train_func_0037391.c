select_source (pixma_t * s)
{
  iclass_t *mf = (iclass_t *) s->subdriver;
  uint8_t *data = pixma_newcmd (&mf->cb, cmd_select_source, 10, 0);
  data[0] = (s->param->source == PIXMA_SOURCE_ADF ||
             s->param->source == PIXMA_SOURCE_ADFDUP) ? 2 : 1;
  data[5] = (s->param->source == PIXMA_SOURCE_ADFDUP) ? 3 : 0;
  switch (s->cfg->pid)
    {
    case MF4200_PID:
    case MF4600_PID:
    case MF6500_PID:
    case D480_PID:
    case D420_PID:
    case MF4360_PID:
    case MF4100_PID:
      return iclass_exec (s, &mf->cb, 0);
      break;
    default:
      return pixma_exec (s, &mf->cb);
    }
}
