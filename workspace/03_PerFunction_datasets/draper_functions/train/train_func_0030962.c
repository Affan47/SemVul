restore_part_field_pointers(Field **ptr, uchar **restore_ptr)
{
  Field *field;
  while ((field= *(ptr++)))
  {
    field->ptr= *restore_ptr;
    restore_ptr++;
  }
  return;
}
