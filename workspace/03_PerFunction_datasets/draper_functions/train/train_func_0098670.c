RemovePointer(table, index)
  PointerTable	*table;
  I		index;
{
  if (table != NULL && index >= 0 && index < table->length)
    table->ptr[index] = (void *)(-1);
}
