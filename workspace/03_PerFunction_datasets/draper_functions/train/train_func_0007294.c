imFileGetAttributeList(imFile* ifile, char** attrib, int *attrib_count)
{
  assert(ifile);
  assert(attrib_count);

  imAttribTable* attrib_table = (imAttribTable*)ifile->attrib_table;
  *attrib_count = attrib_table->Count();

  if (attrib) attrib_table->ForEach((void*)attrib, iAttribCB);
}
