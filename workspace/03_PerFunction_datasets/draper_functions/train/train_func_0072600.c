FslSetFileType(FSLIO *fslio, int filetype)
{
  if (fslio==NULL)  FSLIOERR("FslSetFileType: Null pointer passed for FSLIO");
  if ( (filetype==FSL_TYPE_MINC) || (filetype==FSL_TYPE_MINC_GZ) ) {
    fslio->file_mode = filetype;
    return;
  }
  if (! FslIsValidFileType(filetype)) { return; }
  fslio->file_mode = filetype;
  if (fslio->niftiptr!=NULL) {
    fslio->niftiptr->nifti_type = FslBaseFileType(filetype);
    nifti_set_iname_offset(fslio->niftiptr);
  }
}
