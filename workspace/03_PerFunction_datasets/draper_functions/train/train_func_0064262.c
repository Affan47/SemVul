send_scan_param (pixma_t * s)
{
  mp730_t *mp = (mp730_t *) s->subdriver;
  uint8_t *data;

  data = pixma_newcmd (&mp->cb, cmd_scan_param, 0x2e, 0);
  pixma_set_be16 (s->param->xdpi | 0x1000, data + 0x04);
  pixma_set_be16 (s->param->ydpi | 0x1000, data + 0x06);
  pixma_set_be32 (s->param->x, data + 0x08);
  pixma_set_be32 (s->param->y, data + 0x0c);
  pixma_set_be32 (mp->raw_width, data + 0x10);
  pixma_set_be32 (s->param->h, data + 0x14);

  if (s->param->channels == 1)
    {
      if (s->param->depth == 1)
        data[0x18] = 0x01;
      else
        data[0x18] = 0x04;
    }
  else
    data[0x18] = 0x08;

  data[0x19] = s->param->channels * s->param->depth;
  data[0x1e] = (s->param->depth == 1) ? 0x80 : 0x00;
  data[0x1f] = (s->param->depth == 1) ? 0x80 : 0x7f;
  data[0x20] = (s->param->depth == 1) ? 0x01 : 0xff;
  data[0x23] = 0x81;

  return pixma_exec (s, &mp->cb);
}
