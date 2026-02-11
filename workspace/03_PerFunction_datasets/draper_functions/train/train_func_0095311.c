iMergeFunc(void* user_data, int index, const char* name, int data_type, int count, const void* data)
{
  (void)index;
  imAttribTablePrivate* ptable = (imAttribTablePrivate*)user_data;
  if (!imAttribTableGet(ptable, name, NULL, NULL))
    imAttribTableSet(ptable, name, data_type, count, data);
  return 1;
}
