readDoubleFields(istrstream*& data_line, int nof_fields, double* buffer)
{


  int counter;
  for(counter = 0; counter < nof_fields; counter++) {
    getDataField(data_line, dataFieldBuffer);
    buffer[counter] = atof(dataFieldBuffer);
  }

  return counter;
}
