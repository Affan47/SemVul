MakeQuadrangles(double costheta)
{
  if (verbosity>2)
    cout << "  -- MakeQuadrangles costheta = " << costheta << endl;
  if (verbosity>5)
    cout << "    (in)  Nb of Quadrilaterals = " << NbOfQuad
	 << " Nb Of Triangles = " << nbt-NbOutT- NbOfQuad*2
         << " Nb of outside triangles = " << NbOutT << endl;

  if (costheta >1) {
    if (verbosity>5)
      cout << "     do nothing costheta >1 "<< endl;
    return;}


  Int4 nbqq = (nbt*3)/2;
  DoubleAndInt4  *qq = new DoubleAndInt4[nbqq];

  Int4 i,ij;
  int j;
  Int4 k=0;
  for (i=0;i<nbt;i++)
    for (j=0;j<3;j++)
      if ((qq[k].q=triangles[i].QualityQuad(j))>=costheta)
 	   qq[k++].i3j=i*3+j;

  HeapSort(qq,k);

  Int4 kk=0;
  for (ij=0;ij<k;ij++)
    {

      i=qq[ij].i3j/3;
      j=(int) (qq[ij].i3j%3);

      if (triangles[i].QualityQuad(j,0) >=costheta)
        triangles[i].SetHidden(j),kk++;
    }
  NbOfQuad = kk;
  if (verbosity>2)
    {
    cout << "    (out)  Nb of Quadrilaterals = " << NbOfQuad
	 << " Nb Of Triangles = " << nbt-NbOutT- NbOfQuad*2
         << " Nb of outside triangles = " << NbOutT << endl;
    }
  delete [] qq;
#ifdef DRAWING2
  Draw();
  inquire();
#endif

}
