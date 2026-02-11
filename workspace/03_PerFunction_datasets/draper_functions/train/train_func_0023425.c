read_102(IgesDirectoryEntry* de, bool check_only_status)
{
  bool result = true;

  locateParamEntry(de);

  int i;
  int int_fld, int_fldb[1];
  char chr_fld;

  istrstream* data_line;

  readDataLine(lineBuffer, dataBuffer);
  data_line = new istrstream(dataBuffer);


  int nof_crvs;
  *data_line >> int_fld >> chr_fld;
  *data_line >> nof_crvs >> chr_fld;

  int* crv_id_table = new int[nof_crvs];

  IgesDirectoryEntry* comp_de;


  for(i = 0; i < nof_crvs; i++) {
    readIntFields(data_line, 1, int_fldb);
    crv_id_table[i] = int_fldb[0];

    comp_de = getDirectoryEntry(int_fldb[0]);
    comp_de->referingId = de->id;
  }

  delete [] crv_id_table;

  return result;
}
