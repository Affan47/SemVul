dtype(const string& filename)
{
  Tracer trcr("dtype");
  if ( filename.size()<1 ) return -1;
  string basename = fslbasename(filename);

  FSLIO* IP1;
  IP1 = FslOpen(basename.c_str(),"rb");
  if (IP1==NULL) {
    cerr << "Cannot open volume " << basename << " for reading!\n";
    exit(1);
  }

  short dtype;
  FslGetDataType(IP1,&dtype);
  float slope, intercept;
  int doscaling;
  doscaling = FslGetIntensityScaling(IP1,&slope,&intercept);
  if (doscaling==1) { dtype = DT_FLOAT; }
  FslClose(IP1);
  free(IP1);

  return dtype;
}
