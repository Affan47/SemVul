evas_smart_data_get(const Evas_Smart *s)
{
   MAGIC_CHECK(s, Evas_Smart, MAGIC_SMART);
   return NULL;
   MAGIC_CHECK_END();
   return (void *)s->smart_class->data;
}
