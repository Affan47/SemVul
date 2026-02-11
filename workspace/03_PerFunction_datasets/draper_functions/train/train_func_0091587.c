FslReadTimeSeries(FSLIO *fslio, void *buffer, short xVox, short yVox, short zVox,
                         size_t nvols)
{
  size_t volbytes, offset, orig_offset;
  size_t n;
  short xdim,ydim,zdim,v,wordsize;

  if (fslio==NULL)  FSLIOERR("FslReadTimeSeries: Null pointer passed for FSLIO");
  if (fslio->niftiptr!=NULL) {

    FslGetDim(fslio,&xdim,&ydim,&zdim,&v);

    if ((xVox<0) || (xVox >=xdim)) FSLIOERR("FslReadTimeSeries: voxel outside valid range");
    if ((yVox<0) || (yVox >=ydim)) FSLIOERR("FslReadTimeSeries: voxel outside valid range");
    if ((zVox<0) || (zVox >=zdim)) FSLIOERR("FslReadTimeSeries: voxel outside valid range");

    wordsize = fslio->niftiptr->nbyper;
    volbytes = xdim * ydim * zdim * wordsize;

    orig_offset = znztell(fslio->fileptr);
    offset = ((ydim * zVox + yVox) * xdim + xVox) * wordsize;
    znzseek(fslio->fileptr,offset,SEEK_CUR);

    for (n=0; n<nvols; n++) {
      if (n>0) znzseek(fslio->fileptr, volbytes - wordsize, SEEK_CUR);
      if (znzread((char *)buffer+(n*wordsize), 1, wordsize,fslio->fileptr) != wordsize)
        FSLIOERR("FslReadTimeSeries: failed to read values");
      if (fslio->niftiptr->byteorder != nifti_short_order())
        nifti_swap_Nbytes(1,fslio->niftiptr->swapsize,
                          (char *)buffer+(n*wordsize));
    }


    znzseek(fslio->fileptr,orig_offset,SEEK_SET);
    return n;

  }
  if (fslio->mincptr!=NULL) {
    fprintf(stderr,"Warning:: Minc is not yet supported\n");
  }
  return 0;
}
