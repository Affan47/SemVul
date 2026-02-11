evt_rec_add_tagsv(EVTREC *e, va_list tags)
{
  EVTTAG *t;

  t = va_arg(tags, EVTTAG *);
  while (t)
    {
      evt_rec_add_tag(e, t);
      t = va_arg(tags, EVTTAG *);
    }
}
