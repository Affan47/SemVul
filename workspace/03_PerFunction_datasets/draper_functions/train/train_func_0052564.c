r_unpackextdata(const byte *pdata, ExtDataRec *data)
{
  int i;

  for (i = 0; i < 3; ++i)
    {
      d_fetchuw(&pdata, &(*data)[i].xdrStABN);
      d_fetchuw(&pdata, &(*data)[i].xdrNumABlks);
    }
}
