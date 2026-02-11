evas_key_modifier_on(Evas *e, const char *keyname)
{
   Evas_Modifier_Mask num;
   int n;

   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return;
   MAGIC_CHECK_END();
   n = (Evas_Modifier_Mask)evas_key_modifier_number(&(e->modifiers), keyname);
   if (n < 0) return;
   num = (Evas_Modifier_Mask)n;
   num = 1 << num;
   e->modifiers.mask |= num;
}
