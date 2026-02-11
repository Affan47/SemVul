ReadbbFile(const char * file,long & nbsol,long & lsol,const int typesol,const int dim)
{

  MeshIstream frbb(file);
  int dimlu,typesollu;
  long i;
 double *sol =0;
  frbb >>    dimlu >> nbsol >> lsol >> typesollu ;
  if(typesol != typesollu )
    {
      cerr << " incorrect type of solution (read) " << typesollu << " != (wanted) " <<  typesol << endl;
      cerr << "  or       dim  of solution (read) " << dimlu  << " != (wanted) " <<  dim << endl;
      nbsol=0;
      lsol=0;
    }
  else
    {
      sol = new double[lsol*nbsol];
      double *s=sol;
      for(  i=0;i<lsol;i++)
	for (long j=0;j<nbsol;j++)
	  frbb >>  *s++ ;

    }


  return sol;
}
