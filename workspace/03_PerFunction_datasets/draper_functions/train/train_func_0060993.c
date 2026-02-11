FslGetFileType2(const FSLIO *fslio, int quiet)
{
  FSLIO *mutablefslio;
  if (fslio==NULL)  FSLIOERR("FslGetFileType: Null pointer passed for FSLIO");
  if ( (fslio->file_mode==FSL_TYPE_MINC) || (fslio->file_mode==FSL_TYPE_MINC_GZ) ) {
    return fslio->file_mode;
  }
  if ( !FslIsValidFileType(fslio->file_mode) )    return -1;

  if (fslio->niftiptr!=NULL) {
    if (fslio->niftiptr->nifti_type != FslBaseFileType(fslio->file_mode)) {
      if (!quiet) {
        fprintf(stderr,"Warning: nifti structure and fsl structure disagree on file type\n");
        fprintf(stderr,"nifti = %d and fslio = %d\n",fslio->niftiptr->nifti_type,fslio->file_mode);
      }
      mutablefslio = (FSLIO *) fslio;
      mutablefslio->niftiptr->nifti_type = FslBaseFileType(fslio->file_mode);
      return fslio->file_mode;
    }
 }
  return fslio->file_mode;
}
