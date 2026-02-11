SetInput(u32 count)
{
  inputcount = count;

  datapresentindex = new u32[inputcount];
  datamissingindex = new u32[inputcount];
  database         = new G::ValueType[inputcount];

  G::ValueType base = 1;

  for (unsigned int index=0; index<count; index++)
  {

    datapresentindex[datapresent++] = index;

    database[index] = base++;
  }

  return true;
}
