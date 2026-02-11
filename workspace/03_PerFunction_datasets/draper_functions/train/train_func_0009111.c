ds_strccat (struct dstring *s, char c)
{
  if (s->len + 2 >= s->size)
    ds_grow (s);

  s->content [s->len++] = c;
  s->content [s->len] = '\0';
}
