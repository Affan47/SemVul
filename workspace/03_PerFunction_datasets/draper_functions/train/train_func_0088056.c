imFileGetAttribute(imFile* ifile, const char* attrib, int *data_type, int *count)
{
  assert(ifile);
  assert(attrib);
  imFileFormatBase* ifileformat = (imFileFormatBase*)ifile;
  imAttribTable* attrib_table = (imAttribTable*)ifileformat->attrib_table;
  return attrib_table->Get(attrib, data_type, count);
}
