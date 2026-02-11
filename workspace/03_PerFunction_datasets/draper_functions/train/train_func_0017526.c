Read_amdba(MeshIstream &f_in )
{
  Metric M1(1);
  if (verbosity>1)
    cout << "  -- ReadMesh .amdba file " <<  f_in.CurrentFile  << endl;

     Int4 i;
     f_in.cm() >> nbv >> nbt ;

       cout << "    nbv = " << nbv  << " nbt = " << nbt << endl;
     f_in.eol() ;
     nbvx = nbv;
     nbtx =  2*nbv-2;
     triangles =new Triangle[nbtx];
     assert(triangles);
     vertices=new Vertex[nbvx];
     ordre=new Vertex* [nbvx];
     Int4 j;
      for ( i=0;i<nbv;i++)
	{
	  f_in >> j ;
	  assert( j >0 && j <= nbv);
	  j--;
	  f_in >> vertices[j].r.x >>   vertices[j].r.y >> vertices[j].ReferenceNumber;
	   vertices[j].m=M1;
	   vertices[j].DirOfSearch=NoDirOfSearch;
	}

      for (     i=0;i<nbt;i++)
       {
	 Int4 i1,i2,i3,ref;
	   f_in >> j ;
	   assert( j >0 && j <= nbt);
	   j--;
	   f_in >> i1 >>  i2 >>   i3 >> ref;
	 triangles[j]  = Triangle(this,i1-1,i2-1,i3-1);
	 triangles[j].color =ref;
       }
      f_in.eol() ;


}
