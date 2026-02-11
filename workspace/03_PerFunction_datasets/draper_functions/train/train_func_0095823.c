read_attributes(FILE *in)
{
long marker;
int count;
int len = 0;
int l;

  marker = ftell(in);

  for (count = 0; count < attributes_count; count++)
  {

    attributes[count] = len;
    fseek(in, 2, SEEK_CUR);
    l=read_int32(in);
    fseek(in, l, SEEK_CUR);
    len += sizeof(struct attributes_t) + l;
  }


  attributes_heap = (uint8_t *)malloc(len);
  fseek(in, marker, SEEK_SET);

  struct attributes_t *attribute;
  for (count = 0; count < attributes_count; count++)
  {
    attribute = (struct attributes_t *)(attributes_heap + attributes[count]);
    attribute->name_index = read_int16(in);
    attribute->length = read_int32(in);
    if (fread(attribute->info, 1, attribute->length, in)) {}
  }
}
