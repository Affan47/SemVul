FslGetBufferAsScaledDouble(FSLIO *fslio)
{
  double ****newbuf;
  int xx,yy,zz,tt;
  int ret;
  float inter, slope;

  if (fslio==NULL)  FSLIOERR("FslGetBufferAsScaledDouble: Null pointer passed for FSLIO");

  if ((fslio->niftiptr->dim[0] <= 0) || (fslio->niftiptr->dim[0] > 4))
        FSLIOERR("FslGetBufferAsScaledDouble: Incorrect dataset dimension, 1-4D needed");


  if (fslio->niftiptr!=NULL) {
        xx = (fslio->niftiptr->nx == 0 ? 1 : (long)fslio->niftiptr->nx);
        yy = (fslio->niftiptr->ny == 0 ? 1 : (long)fslio->niftiptr->ny);
        zz = (fslio->niftiptr->nz == 0 ? 1 : (long)fslio->niftiptr->nz);
        tt = (fslio->niftiptr->nt == 0 ? 1 : (long)fslio->niftiptr->nt);

        if (fslio->niftiptr->scl_slope == 0) {
                slope = 1.0;
                inter = 0.0;
        }
        else {
                slope = fslio->niftiptr->scl_slope;
                inter = fslio->niftiptr->scl_inter;
        }


    newbuf = d4matrix(tt-1,zz-1,yy-1,xx-1);


    ret = convertBufferToScaledDouble(newbuf[0][0][0], fslio->niftiptr->data, (long)(xx*yy*zz*tt), slope, inter, fslio->niftiptr->datatype);

    if (ret == 0)
        return(newbuf);
    else
        return(NULL);

  }


  if (fslio->mincptr!=NULL) {
    fprintf(stderr,"Warning:: Minc is not yet supported\n");
  }

  return(NULL);
}
