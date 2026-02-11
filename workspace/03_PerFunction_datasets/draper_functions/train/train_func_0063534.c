select_source (pixma_t * s)
{
  mp730_t *mp = (mp730_t *) s->subdriver;
  uint8_t *data = pixma_newcmd (&mp->cb, cmd_select_source, 10, 0);
  switch (s->param->source)
    {
    case PIXMA_SOURCE_ADF:
      data[0] = 2;
      break;

    case PIXMA_SOURCE_ADFDUP:
      data[0] = 2;
      data[5] = 3;
      break;

    default:
      data[0] = 1;
      break;
    }
  return pixma_exec (s, &mp->cb);
}
