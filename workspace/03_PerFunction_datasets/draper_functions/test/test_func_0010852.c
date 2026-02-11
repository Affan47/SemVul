BoundAnisotropy(Real8 anisomax,Real8 hminaniso)
{
  double lminaniso = 1/ (Max(hminaniso*hminaniso,1e-100));
  if (verbosity > 1)
    cout << "  -- BoundAnisotropy by  " << anisomax << endl;
  Real8 h1=1.e30,h2=1e-30,rx=0;
  Real8 coef = 1./(anisomax*anisomax);
  Real8 hn1=1.e30,hn2=1e-30,rnx =1.e-30;
  for (Int4 i=0;i<nbv;i++)
    {

      MatVVP2x2 Vp(vertices[i]);
      double lmax=Vp.lmax();
      h1=Min(h1,Vp.lmin());
      h2=Max(h2,Vp.lmax());
      rx = Max(rx,Vp.Aniso2());

      Vp *= Min(lminaniso,lmax)/lmax;

      Vp.BoundAniso2(coef);

      hn1=Min(hn1,Vp.lmin());
      hn2=Max(hn2,Vp.lmax());
      rnx = Max(rnx,Vp.Aniso2());


      vertices[i].m = Vp;

    }

  if (verbosity>2)
    {
      cout << "     input :  Hmin = " << sqrt(1/h2)  << " Hmax = " << sqrt(1/h1)
	   << " factor of anisotropy max  = " << sqrt(rx) << endl;
      cout << "     output:  Hmin = " << sqrt(1/hn2) << " Hmax = " << sqrt(1/hn1)
	   << " factor of anisotropy max  = " << sqrt(rnx) << endl;
    }
}
