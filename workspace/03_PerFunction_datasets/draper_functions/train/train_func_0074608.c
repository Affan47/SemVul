sge_dstring_copy_dstring(dstring *sb1, const dstring *sb2)
{
   const char *ret = NULL;

   DENTER(DSTRING_LAYER, "sge_dstring_copy_dstring");

   if (sb1 != NULL) {
      sge_dstring_clear(sb1);
      ret = sge_dstring_append(sb1, sge_dstring_get_string(sb2));
   }

   DEXIT;
   return ret;
}
