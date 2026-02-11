mxml_write_attribute(MXML_WRITER *writer, const char *name, const char *value)
{
   char name_enc[4096], val_enc[4096], line[8192];

   if (!writer->element_is_open)
      return FALSE;

   strcpy(name_enc, name);
   mxml_encode(name_enc, sizeof(name_enc), writer->translate);
   strcpy(val_enc, value);
   mxml_encode(val_enc, sizeof(val_enc), writer->translate);

   sprintf(line, " %s=\"%s\"", name_enc, val_enc);

   return mxml_write_line(writer, line) == (int)strlen(line);
}
