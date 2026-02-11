read_fields(FILE *in)
{
long marker;
int count;
int len = 0;
int n,l,r;

  marker = ftell(in);

  for (count = 0; count < fields_count; count++)
  {

    fields[count] = len;
    fseek(in, 6, SEEK_CUR);
    n = read_int16(in);
    len += sizeof(struct fields_t);
    for (r = 0; r < n; r++)
    {
      fseek(in, 2, SEEK_CUR);
      l = read_int32(in);
      len += sizeof(struct attributes_t) + l;
      fseek(in, l, SEEK_CUR);
    }
  }


  fields_heap = (uint8_t *)malloc(len);
  fseek(in, marker, SEEK_SET);

  struct attributes_t *attribute;
  struct fields_t *field;
  for (count = 0; count < fields_count; count++)
  {
    field = (struct fields_t *)(fields_heap + fields[count]);
    field->access_flags = read_int16(in);
    field->name_index = read_int16(in);
    field->descriptor_index = read_int16(in);
    field->attribute_count = read_int16(in);
    n = sizeof(struct fields_t);
    for (r = 0; r < field->attribute_count; r++)
    {
      attribute = (struct attributes_t *)(fields_heap + fields[count]+n);
      attribute->name_index = read_int16(in);
      attribute->length = read_int32(in);
      if (fread(attribute->info, 1, attribute->length, in)) {}
      n = n + 6 + attribute->length;
    }
  }
}
