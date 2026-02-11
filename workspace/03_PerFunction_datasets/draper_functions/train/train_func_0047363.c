save_complexvolume4D(const volume4D<float>& realvols,
			 const volume4D<float>& imagvols,
			 const string& filename)
{
  Tracer tr("save_complexvolume4D");

  if (realvols.tsize()<=0) return -1;

  string basename = filename;
  make_basename(basename);
  if ( basename.size()<1 ) return -1;


  if (!realvols[0].RadiologicalFile) { const_cast< volume4D <float>& > (realvols).makeneurological(); }
  if (!imagvols[0].RadiologicalFile) { const_cast< volume4D <float>& > (imagvols).makeneurological(); }

  FSLIO* OP=FslOpen(basename.c_str(),"w");
  if (OP==0) return -1;
  set_fsl_hdr(realvols[0],OP,realvols.tsize(),realvols.tdim());
  FslSetDataType(OP, DT_COMPLEX);

  FslWriteHeader(OP);

  for (int t=0; t<realvols.tsize(); t++) {
    FslWriteComplexVolume(OP,&(realvols[t](0,0,0)),&(imagvols[t](0,0,0)));
  }

  FslClose(OP);


  if (!realvols[0].RadiologicalFile) { const_cast< volume4D <float>& > (realvols).makeradiological(); }
  if (!imagvols[0].RadiologicalFile) { const_cast< volume4D <float>& > (imagvols).makeradiological(); }
  return 0;
}
