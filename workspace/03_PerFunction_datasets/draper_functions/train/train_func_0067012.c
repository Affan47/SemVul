one_slice_AtA(const NEWMAT::Matrix&   Bx,
                             const NEWMAT::Matrix&   By,
                             const double            *ima,
                             double                  *AtA) const
{
  NEWMAT::Matrix           XtX(Bx.Ncols(),Bx.Ncols());
  NEWMAT::Matrix           Bxt = Bx.t();
  NEWMAT::DiagonalMatrix   pima(Bx.Nrows());
  int                      xnc = Bx.Ncols();
  int                      ync = By.Ncols();
  int                      AtAsz = xnc*ync;

  memset(AtA,0,SQR(AtAsz)*sizeof(double));
  for (int my=0; my<By.Nrows(); my++) {
    const double *iptr = &(ima[my*Bx.Nrows()]);
    pima << iptr;
    XtX = Bxt*pima*Bx;
    double *XtXp = XtX.Store();

    for (int yr=0; yr<ync; yr++) {
      for (int yc=yr; yc<ync; yc++) {
        double scl = By.element(my,yr)*By.element(my,yc);
	for (int xr=0; xr<xnc; xr++) {
	  for (int xc=xr; xc<xnc; xc++) {
            AtA[(yr*xnc+xr)*AtAsz + yc*xnc+xc] += scl*XtXp[xr*xnc+xc];
	  }
	}
      }
    }
  }


  for (int yr=0; yr<ync; yr++) {
    for (int yc=yr; yc<ync; yc++) {
      for (int xr=0; xr<xnc; xr++) {
	for (int xc=0; xc<xr; xc++) {
	  AtA[(yr*xnc+xr)*AtAsz + yc*xnc+xc] = AtA[(yr*xnc+xc)*AtAsz + yc*xnc+xr];
	}
      }
    }
  }


  for (int yr=0; yr<ync; yr++) {
    for (int yc=0; yc<yr; yc++) {
      for (int xr=0; xr<xnc; xr++) {
	for (int xc=0; xc<xnc; xc++) {
	  AtA[(yr*xnc+xr)*AtAsz + yc*xnc+xc] = AtA[(yc*xnc+xc)*AtAsz + yr*xnc+xr];
	}
      }
    }
  }


}
