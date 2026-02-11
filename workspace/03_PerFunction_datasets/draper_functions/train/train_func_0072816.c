create_spooling_field (
   spooling_field *field,
   int nm,
   int width,
   const char *name,
   struct spooling_field *sub_fields,
   const void *clientdata,
   int (*read_func) (lListElem *ep, int nm, const char *buffer, lList **alp),
   int (*write_func) (const lListElem *ep, int nm, dstring *buffer, lList **alp)
)
{
   if (field != NULL) {
      field->nm = nm;
      field->width = width;
      field->name = name;
      field->sub_fields = sub_fields;
      field->clientdata = clientdata;
      field->read_func = read_func;
      field->write_func = write_func;
   }
}
