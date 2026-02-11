MLEndData(hs, data, len)
MLState hs;
char *data;
size_t len;
{
  MLElement p;
  size_t poff;

  if (data == NULL || len == 0 || len < hs->off) return;

  hs_handle_data(hs, data, len, true);

  poff = hs_pop(hs);
  if (len - poff > 0)
  {
    if (IN_STATE(hs, MLS_DATA))
    {
      p = hs_create_text(hs, hs->data + poff, len - poff);
    }
    else
    {
      p = hs_create_tag(hs, hs->data + poff, len - poff);
    }
    hs_add_element(hs, p);
  }

  p = (MLElement)MPCGet(hs->mp, sizeof(struct MLElementP));
  p->type = ML_EOF;
  hs_add_element(hs, p);

  MPDestroy(hs->tmp);
  hs->tmp = NULL;

  return;
}
