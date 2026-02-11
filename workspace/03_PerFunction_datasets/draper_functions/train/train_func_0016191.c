hpmud_query_model(char *uri, struct hpmud_model_attributes *ma)
{
   char buf[SECTION_SIZE];
   int len;
   enum HPMUD_RESULT stat = HPMUD_R_DATFILE_ERROR;

   parse_key_value_pair(NULL, 0, ma);

   if (hpmud_get_model_attributes(uri, buf, sizeof(buf), &len) != 0)
      goto bugout;

   parse_key_value_pair(buf, len, ma);

   stat=HPMUD_R_OK;

bugout:

   return stat;
}
